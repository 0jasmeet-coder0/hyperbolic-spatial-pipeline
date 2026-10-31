#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <cstdlib>
#include <map>

struct Entity {
    double x, y;
    int id; // Global unique identifier
};

// Math Baselines
double getNormalDistance(double x1, double y1, double x2, double y2) {
    return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double getWarpedDistance(double x1, double y1, double x2, double y2) {
    double normalDist = getNormalDistance(x1, y1, x2, y2);
    double r1 = std::sqrt(x1 * x1 + y1 * y1);
    double r2 = std::sqrt(x2 * x2 + y2 * y2);
    double scale = 1.0 / (1.0 - (r1 * r2 * 0.0001));
    return normalDist * std::abs(scale);
}

int main() {
    const int ENTITY_COUNT = 1000;
    const double GRID_CELL_SIZE = 1.0; 
    std::vector<Entity> entities(ENTITY_COUNT);

    // Seed random positions and assign continuous tracking IDs
    for (int i = 0; i < ENTITY_COUNT; ++i) {
        entities[i].x = (rand() % 200 - 100) * 0.1;
        entities[i].y = (rand() % 200 - 100) * 0.1;
        entities[i].id = i;
    }

    std::cout << "Starting spatial grid optimization benchmarks...\n\n";

    // --- BENCHMARK 1: Unoptimized Non-Euclidean Loop ---
    auto startWarped = std::chrono::high_resolution_clock::now();
    int warpedCollisions = 0;
    for (int i = 0; i < ENTITY_COUNT; ++i) {
        for (int j = i + 1; j < ENTITY_COUNT; ++j) {
            double dist = getWarpedDistance(entities[i].x, entities[i].y, entities[j].x, entities[j].y);
            if (dist < 0.5) warpedCollisions++;
        }
    }
    auto endWarped = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> durationWarped = endWarped - startWarped;

    // --- BENCHMARK 2: Optimized Spatial Grid Partitioning ---
    auto startOptimized = std::chrono::high_resolution_clock::now();
    int optimizedCollisions = 0;
    
    // Hash grid bucket system mapped to structured vectors
    std::map<std::pair<int, int>, std::vector<Entity>> spatialGrid;
    
    // Assign entities directly to localized spatial buckets
    for (int i = 0; i < ENTITY_COUNT; ++i) {
        int cellX = std::floor(entities[i].x / GRID_CELL_SIZE);
        int cellY = std::floor(entities[i].y / GRID_CELL_SIZE);
        spatialGrid[{cellX, cellY}].push_back(entities[i]);
    }

    // Classic Iterator loop to scan spatial buckets securely
    std::map<std::pair<int, int>, std::vector<Entity>>::iterator it;
    for (it = spatialGrid.begin(); it != spatialGrid.end(); ++it) {
        std::pair<int, int> cellCoord = it->first;
        std::vector<Entity> currentBucket = it->second;
        
        int cx = cellCoord.first;
        int cy = cellCoord.second;

        // Check current cell and immediate 8 neighboring blocks
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                std::map<std::pair<int, int>, std::vector<Entity>>::iterator neighborIt = spatialGrid.find({cx + dx, cy + dy});
                
                if (neighborIt != spatialGrid.end()) {
                    std::vector<Entity> neighborBucket = neighborIt->second;
                    
                    // Loop through active bucket configurations
                    for (size_t i = 0; i < currentBucket.size(); ++i) {
                        for (size_t j = 0; j < neighborBucket.size(); ++j) {
                            // Enforce strict index alignment rules to bypass double calculations
                            if (currentBucket[i].id >= neighborBucket[j].id) continue;
                            
                            double dist = getWarpedDistance(currentBucket[i].x, currentBucket[i].y, neighborBucket[j].x, neighborBucket[j].y);
                            if (dist < 0.5) optimizedCollisions++;
                        }
                    }
                }
            }
        }
    }
    auto endOptimized = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> durationOptimized = endOptimized - startOptimized;

    // --- DISPLAY PERFORMANCE METRICS ---
    std::cout << "=== UNOPTIMIZED WARPED EXECUTION ===\n";
    std::cout << "Execution Time: " << durationWarped.count() << " ms\n";
    std::cout << "Detected Proximities: " << warpedCollisions << "\n\n";

    std::cout << "=== OPTIMIZED SPATIAL GRID EXECUTION ===\n";
    std::cout << "Execution Time: " << durationOptimized.count() << " ms\n";
    std::cout << "Detected Proximities: " << optimizedCollisions << "\n\n";
    
    double performanceGain = ((durationWarped.count() - durationOptimized.count()) / durationWarped.count()) * 100.0;
    std::cout << "Total Algorithmic Performance Boost: " << performanceGain << "%\n";

    return 0;
}
