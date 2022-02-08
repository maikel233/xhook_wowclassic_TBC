#include "AmeisonNavigation.h"
#include <filesystem>

#define PRINT_VEC3(vec) "[" << vec.x << ", " << vec.y << ", " << vec.z << "]"

std::string AmeisenNavigation::FormatTrailingZeros(const int number, const int zeroCount)
{
    std::stringstream ss;
    ss << std::setw(zeroCount) << std::setfill('0') << number;
    return ss.str();
}

bool AmeisenNavigation::IsMmapLoaded(const int map_id)
{
    return mNavMeshMap[map_id] != nullptr
        && mNavMeshQueryMap[map_id] != nullptr;
}
int MaxPathNodes = 1028;
void AmeisenNavigation::SmoothPathChaikinCurve(Vector3* Path, int inputSize, Vector3* output, int* outputSize) const noexcept
{
    InsertVector3(reinterpret_cast<float*>(output), *outputSize, reinterpret_cast<float*>(Path), 0);

    // buffers to scale and add vectors
    float s0[3];
    float s1[3];

    float result[3];

    // make sure we dont go over the buffer bounds
    // why 9: we add 6 floats in the loop and 3 for the end position
    const int maxIndex = MaxPathNodes - 9;

    for (int i = 0; i < inputSize - 3; i += 3)
    {
        if (*outputSize > maxIndex) { break; }

        ScaleAndAddVector3(reinterpret_cast<float*>(Path) + i, 0.75f, reinterpret_cast<float*>(Path) + i + 3, 0.25f, s0, s1, result);
        InsertVector3(reinterpret_cast<float*>(output), *outputSize, result, 0);

        ScaleAndAddVector3(reinterpret_cast<float*>(Path) + i, 0.25f, reinterpret_cast<float*>(Path) + i + 3, 0.75f, s0, s1, result);
        InsertVector3(reinterpret_cast<float*>(output), *outputSize, result, 0);
    }

    InsertVector3(reinterpret_cast<float*>(output), *outputSize, reinterpret_cast<float*>(Path), inputSize - 3);
}

void AmeisenNavigation::SmoothPathCatmullRom(Vector3* Path, int inputSize, Vector3* output, int* outputSize, int points, float alpha) const noexcept
{
    InsertVector3(reinterpret_cast<float*>(output), *outputSize, reinterpret_cast<float*>(Path), 0);

    // buffers to scale and add vectors
    float s0[3];
    float s1[3];

    float A1[3];
    float A2[3];
    float A3[3];

    float B1[3];
    float B2[3];

    float C[3];

    // make sure we dont go over the buffer bounds
    // why 3: we add 3 floats in the loop
    const int maxIndex = MaxPathNodes - 3;

    for (int i = 3; i < inputSize - 6; i += 3)
    {
        const float* p0 = reinterpret_cast<float*>(Path) + i - 3;
        const float* p1 = reinterpret_cast<float*>(Path) + i;
        const float* p2 = reinterpret_cast<float*>(Path) + i + 3;
        const float* p3 = reinterpret_cast<float*>(Path) + i + 6;

        const float t0 = 0.0f;

        const float t1 = std::powf(std::powf(p1[0] - p0[0], 2.0f) + std::powf(p1[1] - p0[1], 2.0f) + std::powf(p1[2] - p0[2], 2.0f), alpha * 0.5f) + t0;
        const float t2 = std::powf(std::powf(p2[0] - p1[0], 2.0f) + std::powf(p2[1] - p1[1], 2.0f) + std::powf(p2[2] - p1[2], 2.0f), alpha * 0.5f) + t1;
        const float t3 = std::powf(std::powf(p3[0] - p2[0], 2.0f) + std::powf(p3[1] - p2[1], 2.0f) + std::powf(p3[2] - p2[2], 2.0f), alpha * 0.5f) + t2;

        for (float t = t1; t < t2; t += ((t2 - t1) / static_cast<float>(points)))
        {
            ScaleAndAddVector3(p0, (t1 - t) / (t1 - t0), p1, (t - t0) / (t1 - t0), s0, s1, A1);
            ScaleAndAddVector3(p1, (t2 - t) / (t2 - t1), p2, (t - t1) / (t2 - t1), s0, s1, A2);
            ScaleAndAddVector3(p2, (t3 - t) / (t3 - t2), p3, (t - t2) / (t3 - t2), s0, s1, A3);

            ScaleAndAddVector3(A1, (t2 - t) / (t2 - t0), A2, (t - t0) / (t2 - t0), s0, s1, B1);
            ScaleAndAddVector3(A2, (t3 - t) / (t3 - t1), A3, (t - t1) / (t3 - t1), s0, s1, B2);

            ScaleAndAddVector3(B1, (t2 - t) / (t2 - t1), B2, (t - t1) / (t2 - t1), s0, s1, C);

            if (!std::isnan(C[0]) && !std::isnan(C[1]) && !std::isnan(C[2]))
            {
                if (*outputSize > maxIndex) { return; }

                InsertVector3(reinterpret_cast<float*>(output), *outputSize, C, 0);
            }
        }
    }
}
//
//bool AmeisenNavigation::GetRandomPath(const int mapId, const Vector3& startPosition, const Vector3& endPosition, Vector3* path, int* pathSize, float maxRandomDistance)
//{
//    D(std::cout << ">> GetPath (" << mapId << ") " << startPosition << " -> " << endPosition << std::endl);
//
//    Vector3 startPositionRd = Vector3(startPosition);
//    WowToRDCoords(startPositionRd);
//
//    Vector3 endPositionRd = Vector3(endPosition);
//    WowToRDCoords(endPositionRd);
//
//    D(std::cout << ">> GetPath RD Coordinates (" << mapId << ") " << startPositionRd << " -> " << endPositionRd << std::endl);
//
//    if (!PreparePathfinding(mapId))
//    {
//        *pathSize = 0;
//        return false;
//    }
//
//    Vector3 closestPointStart;
//    Vector3 closestPointEnd;
//
//    dtPolyRef startPoly = GetNearestPoly(mapId, startPositionRd, &closestPointStart);
//    dtPolyRef endPoly = GetNearestPoly(mapId, endPositionRd, &closestPointEnd);
//
//    dtPolyRef* visitedBuffer = GetMiscPathBuffer();
//
//    D(std::cout << ">> closestPointStart (" << mapId << ") " << closestPointStart << std::endl);
//    D(std::cout << ">> closestPointEnd (" << mapId << ") " << closestPointEnd << std::endl);
//
//    if (startPoly == endPoly)
//    {
//        // same poly, we don't need pathfinding here
//        D(std::cout << ">> Start and End positions are on the same poly, returning end position" << std::endl);
//
//        *pathSize = 1;
//        path[0] = endPosition;
//        return true;
//    }
//    else
//    {
//        const std::unique_ptr<dtPolyRef> polypath(new dtPolyRef[maxPolyPath]);
//        int polypathSize = 0;
//
//        if (dtStatusSucceed(mNavMeshQueryMap[mapId]->findPath(startPoly, endPoly, reinterpret_cast<const float*>(&closestPointStart), reinterpret_cast<const float*>(&closestPointEnd), &mQueryFilter, polypath.get(), &polypathSize, maxPolyPath)))
//        {
//            D(std::cout << ">> PolyPath size: " << polypathSize << "/" << maxPolyPath << std::endl);
//
//            for (int i = 0; i < *pathSize; i += 3)
//            {
//                if (i > 0 && i < *pathSize - 3)
//                {
//
//                    dtStatus randomPointStatus = mNavMeshQueryMap[mapId]->findRandomPointAroundCircle
//                    (
//                        visitedBuffer[i / 3],
//                        reinterpret_cast<float*>(path),
//                        maxRandomDistance,
//                        &QueryFilter,
//                        GetRandomFloat,
//                        &randomRef,
//                        path + i
//                    );
//
//                    if (dtStatusFailed(randomPointStatus))
//                    {
//                        std::cout << ">> [" << "] Failed to call findRandomPointAroundCircle: " << randomPointStatus << std::endl;
//                    }
//                }
//
//                RDToWowCoords(path[i]);
//            }
//
//            return true;
//        }
//
//        return false;
//    }
//

bool AmeisenNavigation::GetPath(const int mapId, const Vector3& startPosition, const Vector3& endPosition, Vector3* path, int* pathSize)
{
    D(std::cout << ">> GetPath (" << mapId << ") " << startPosition << " -> " << endPosition << std::endl);

    Vector3 startPositionRd = Vector3(startPosition);
    WowToRDCoords(startPositionRd);

    Vector3 endPositionRd = Vector3(endPosition);
    WowToRDCoords(endPositionRd);

    D(std::cout << ">> GetPath RD Coordinates (" << mapId << ") " << startPositionRd << " -> " << endPositionRd << std::endl);

    if (!PreparePathfinding(mapId))
    {
        *pathSize = 0;
        return false;
    }

    Vector3 closestPointStart;
    Vector3 closestPointEnd;

    dtPolyRef startPoly = GetNearestPoly(mapId, startPositionRd, &closestPointStart);
    dtPolyRef endPoly = GetNearestPoly(mapId, endPositionRd, &closestPointEnd);

    D(std::cout << ">> closestPointStart (" << mapId << ") " << closestPointStart << std::endl);
    D(std::cout << ">> closestPointEnd (" << mapId << ") " << closestPointEnd << std::endl);

    if (startPoly == endPoly)
    {
        // same poly, we don't need pathfinding here
        D(std::cout << ">> Start and End positions are on the same poly, returning end position" << std::endl);

        *pathSize = 1;
        path[0] = endPosition;
        return true;
    }
    else
    {
        const std::unique_ptr<dtPolyRef> polypath(new dtPolyRef[maxPolyPath]);
        int polypathSize = 0;

        if (dtStatusSucceed(mNavMeshQueryMap[mapId]->findPath(startPoly, endPoly, reinterpret_cast<const float*>(&closestPointStart), reinterpret_cast<const float*>(&closestPointEnd), &mQueryFilter, polypath.get(), &polypathSize, maxPolyPath)))
        {
            D(std::cout << ">> PolyPath size: " << polypathSize << "/" << maxPolyPath << std::endl);

            if (dtStatusSucceed(mNavMeshQueryMap[mapId]->findStraightPath
            (
                reinterpret_cast<const float*>(&closestPointStart),
                reinterpret_cast<const float*>(&closestPointEnd),
                polypath.get(), polypathSize,
                reinterpret_cast<float*>(path),
                nullptr,
                nullptr,
                pathSize,
                maxPointPath * 3
            )))

            {
                D(std::cout << ">> PointPath size: " << (*pathSize) << "/" << maxPointPath << std::endl);

                // convert to Recast and Detour coordinates to Wow coordinates
                for (int i = 0; i < (*pathSize); ++i)
                {
                    RDToWowCoords(path[i]);
                }

                return true;
            }
            else
            {
                std::cerr << ">> findStraightPath failed (mapId: " << mapId << ")" << std::endl;
            }
        }
        else
        {
            std::cerr << ">> findPath failed (mapId: " << mapId << ")" << std::endl;
        }

        *pathSize = 0;
        path = nullptr;
        return false;
    }
}


bool AmeisenNavigation::PreparePathfinding(int mapId)
{
    if (!IsMmapLoaded(mapId))
    {
        D(std::cout << ">> Mesh for Continent " << mapId << " not loaded, loading it now" << std::endl);

        if (!LoadMmapsForContinent(mapId))
        {
            std::cerr << ">> Unable to load MMAPS for continent " << mapId << std::endl;

            return false;
        }
    }

    return true;
}

bool AmeisenNavigation::MoveAlongSurface(const int mapId, const Vector3& startPosition, const Vector3& endPosition, Vector3* positionToGoTo)
{
    D(std::cout << ">> MoveAlongSurface (" << mapId << ") " << startPosition << " -> " << endPosition << std::endl);

    Vector3 startPositionRd = Vector3(startPosition);
    WowToRDCoords(startPositionRd);

    Vector3 endPositionRd = Vector3(endPosition);
    WowToRDCoords(endPositionRd);

    if (!PreparePathfinding(mapId))
    {
        return false;
    }

    int visitedCount;
    dtPolyRef visited[64];
    dtPolyRef startPoly = GetNearestPoly(mapId, startPositionRd, nullptr);

    if (dtStatusSucceed(mNavMeshQueryMap[mapId]->moveAlongSurface(startPoly, reinterpret_cast<const float*>(&startPositionRd), reinterpret_cast<const float*>(&endPositionRd), &mQueryFilter, reinterpret_cast<float*>(positionToGoTo), visited, &visitedCount, 64)))
    {
        RDToWowCoords(*positionToGoTo);
        D(std::cout << ">> Found position to go to " << (*positionToGoTo) << std::endl);

        return true;
    }

    return false;
}

bool AmeisenNavigation::GetRandomPoint(const int mapId, Vector3* position)
{
    D(std::cout << ">> GetRandomPoint (" << mapId << ")" << std::endl);

    if (!PreparePathfinding(mapId))
    {
        return false;
    }

    dtPolyRef polyRef;

    if (dtStatusSucceed(mNavMeshQueryMap[mapId]->findRandomPoint(&mQueryFilter, []() { return (float)rand() / (float)(RAND_MAX); }, &polyRef, reinterpret_cast<float*>(position))))
    {
        RDToWowCoords(*position);
        D(std::cout << ">> Found random position " << *position << std::endl);
        return true;
    }

    return false;
}

bool AmeisenNavigation::GetRandomPointAround(const int mapId, const Vector3& startPosition, float radius, Vector3* position)
{
    D(std::cout << ">> GetRandomPointAround (" << mapId << ") startPosition: " << startPosition << " radius: " << radius << std::endl);

    if (!PreparePathfinding(mapId))
    {
        return false;
    }

    Vector3 startPositionRd = Vector3(startPosition);
    WowToRDCoords(startPositionRd);

    Vector3 closestPoint;
    dtPolyRef startPoly = GetNearestPoly(mapId, startPositionRd, &closestPoint);

    D(std::cout << ">> GetRandomPointAround (" << mapId << ") closestPoint: " << closestPoint << " startPoly: " << startPoly << std::endl);

    dtPolyRef polyRef;

    if (dtStatusSucceed(mNavMeshQueryMap[mapId]->findRandomPointAroundCircle(startPoly, reinterpret_cast<const float*>(&closestPoint), radius, &mQueryFilter, []() { return (float)rand() / (float)(RAND_MAX); }, &polyRef, reinterpret_cast<float*>(position))))
    {
        RDToWowCoords(*position);
        D(std::cout << ">> Found random position " << *position << std::endl);
        return true;
    }

    return false;
}

bool AmeisenNavigation::CastMovementRay(const int mapId, const Vector3& startPosition, const Vector3& endPosition)
{
    D(std::cout << ">> CastMovementRay (" << mapId << ") " << startPosition << " -> " << endPosition << std::endl);

    Vector3 startPositionRd = Vector3(startPosition);
    WowToRDCoords(startPositionRd);

    Vector3 endPositionRd = Vector3(endPosition);
    WowToRDCoords(endPositionRd);

    if (!PreparePathfinding(mapId))
    {
        return false;
    }

    dtPolyRef startPoly = GetNearestPoly(mapId, startPositionRd, nullptr);
    dtRaycastHit raycastHit;

    dtStatus result = mNavMeshQueryMap[mapId]->raycast(startPoly, reinterpret_cast<const float*>(&startPositionRd), reinterpret_cast<const float*>(&endPositionRd), &mQueryFilter, 0, &raycastHit);

    return dtStatusSucceed(result) && raycastHit.t == FLT_MAX;
}

dtPolyRef AmeisenNavigation::GetNearestPoly(const int mapId, const Vector3& position, Vector3* closestPointOnPoly)
{
    float extents[3] = { 12.0f, 12.0f, 12.0f };

    dtPolyRef polyRef;
    mNavMeshQueryMap[mapId]->findNearestPoly(reinterpret_cast<const float*>(&position), extents, &mQueryFilter, &polyRef, reinterpret_cast<float*>(closestPointOnPoly));

    return polyRef;
}

bool AmeisenNavigation::LoadMmapsForContinent(const int mapId)
{
    // build the *.mmap filename (example: 001.mmap or 587.mmap)
    std::string mmapFilename = mMmapFolder;
    mmapFilename += FormatTrailingZeros(mapId, 3);
    mmapFilename += ".mmap";

    // we can't load non existent files
    if (!std::filesystem::exists(mmapFilename))
    {
        std::cerr << ">> Unable to find mmap file " << " (mapId: " << mapId << ", mmapFilename: \"" << mmapFilename << "\")" << std::endl;
        return false;
    }

    std::ifstream mmapStream;
    mmapStream.open(mmapFilename, std::ifstream::binary);

    // read the dtNavMeshParams
    dtNavMeshParams params;
    mmapStream.read(reinterpret_cast<char*>(&params), sizeof(dtNavMeshParams));
    mmapStream.close();

    // allocate and init the NavMesh
    mNavMeshMap[mapId] = dtAllocNavMesh();

    if (dtStatusFailed(mNavMeshMap[mapId]->init(&params)))
    {
        std::cerr << ">> Unable to init NavMesh " << " (mapId: " << mapId << ", mmapFilename: \"" << mmapFilename << "\")" << std::endl;
        dtFreeNavMesh(mNavMeshMap[mapId]);
        return false;
    }

    // load every NavMesh Tile from 1, 1 to 64, 64
    for (int x = 1; x <= 64; ++x)
    {
        for (int y = 1; y <= 64; ++y)
        {
            std::string mmapTileFilename = mMmapFolder;
            mmapTileFilename += FormatTrailingZeros(mapId, 3);
            mmapTileFilename += FormatTrailingZeros(x, 2);
            mmapTileFilename += FormatTrailingZeros(y, 2);
            mmapTileFilename += ".mmtile";

            // we can't load non existent files
            if (!std::filesystem::exists(mmapTileFilename))
            {
                continue;
            }

          //  D(std::cout << ">> Reading dtTile " << mmapTileFilename.c_str() << std::endl);

            std::ifstream mmapTileStream;
            mmapTileStream.open(mmapTileFilename, std::ifstream::binary);

            // read the mmap header
            MmapTileHeader mmapTileHeader;
            mmapTileStream.read(reinterpret_cast<char*>(&mmapTileHeader), sizeof(MmapTileHeader));

            if (mmapTileHeader.mmapMagic != MMAP_MAGIC)
            {
                std::cerr << ">> Wrong MMAP Magic (got:" << mmapTileHeader.mmapMagic << ", expected:" << MMAP_MAGIC << ") dtTile " << x << " " << y << " (mapId: " << mapId << ")" << std::endl;
                return false;
            }

            if (mmapTileHeader.mmapVersion < MMAP_VERSION)
            {
                std::cerr << ">> Wrong MMAP version (got:" << mmapTileHeader.mmapVersion << ", expected:" << MMAP_VERSION << ") dtTile " << x << " " << y << " (mapId: " << mapId << ")" << std::endl;
                return false;
            }

            // read the NavMesh Tile data
            void* mmapTileData = dtAlloc(mmapTileHeader.size, DT_ALLOC_PERM);
            mmapTileStream.read(reinterpret_cast<char*>(mmapTileData), mmapTileHeader.size);
            mmapTileStream.close();

            // add the Tile to our NavMesh
            dtTileRef tileRef;

            if (dtStatusFailed(mNavMeshMap[mapId]->addTile(reinterpret_cast<unsigned char*>(mmapTileData), mmapTileHeader.size, DT_TILE_FREE_DATA, 0, &tileRef)))
            {
                std::cerr << ">> Failed to add dtTile " << x << " " << y << " to NavMesh (mapId: " << mapId << ")" << std::endl;

                dtFree(mmapTileData);
                dtFreeNavMesh(mNavMeshMap[mapId]);
                return false;
            }
        }
    }

    // init the NavMeshQuery
    mNavMeshQueryMap[mapId] = dtAllocNavMeshQuery();

    if (dtStatusFailed(mNavMeshQueryMap[mapId]->init(mNavMeshMap[mapId], 65535)))
    {
        std::cerr << ">> Failed to init NavMeshQuery (mapId: " << mapId << ")" << std::endl;

        dtFreeNavMeshQuery(mNavMeshQueryMap[mapId]);
        dtFreeNavMesh(mNavMeshMap[mapId]);
        return false;
    }

    return true;
}

////
////bool AmeisenNavigation::LoadMmaps(int mapId)
////{
////    const std::lock_guard<std::mutex> lock(mNavMeshMap[mapId].first);
////
////    if (IsMmapLoaded(mapId)) { return true; }
////
////    // build the *.mmap filename (example: 001.mmap or 587.mmap)
////    std::stringstream mmapFilename;
////    mmapFilename << std::setw(3) << std::setfill('0') << mapId << ".mmap";
////
////    std::filesystem::path mmapFile(MmapFolder);
////    mmapFile.append(mmapFilename.str());
////
////    if (!std::filesystem::exists(mmapFile))
////    {
////        std::cout << ">> MMAP file not found for map '" << mapId << "': " << mmapFile << std::endl;
////        return false;
////    }
////
////    std::ifstream mmapStream;
////    mmapStream.open(mmapFile, std::ifstream::binary);
////
////    dtNavMeshParams params{};
////    mmapStream.read(reinterpret_cast<char*>(&params), sizeof(dtNavMeshParams));
////    mmapStream.close();
////
////    mNavMeshMa[mapId].second = dtAllocNavMesh();
////
////    if (!mNavMeshMap[mapId].second)
////    {
////        std::cout << ">> Failed to allocate NavMesh for map '" << mapId << "'" << std::endl;
////        return false;
////    }
////
////    dtStatus initStatus = NavMeshMap[mapId].second->init(&params);
////
////    if (dtStatusFailed(initStatus))
////    {
////        dtFreeNavMesh(NavMeshMap[mapId].second);
////        std::cout << ">> Failed to init NavMesh for map '" << mapId << "': " << initStatus << std::endl;
////        return false;
////    }
////
////    for (int x = 1; x <= 64; ++x)
////    {
////        for (int y = 1; y <= 64; ++y)
////        {
////            std::stringstream mmapTileFilename;
////            mmapTileFilename << std::setfill('0') << std::setw(3) << mapId << std::setw(2) << x << std::setw(2) << y << ".mmtile";
////
////            std::filesystem::path mmapTileFile(MmapFolder);
////            mmapTileFile.append(mmapTileFilename.str());
////
////            if (!std::filesystem::exists(mmapTileFile))
////            {
////                continue;
////            }
////
////            std::cout << ">> Reading dtTile for map '" << mapId << "': " << mmapTileFile << std::endl;
////
////            std::ifstream mmapTileStream;
////            mmapTileStream.open(mmapTileFile, std::ifstream::binary);
////
////            MmapTileHeader mmapTileHeader{};
////            mmapTileStream.read(reinterpret_cast<char*>(&mmapTileHeader), sizeof(MmapTileHeader));
////
////            if (mmapTileHeader.mmapMagic != MMAP_MAGIC)
////            {
////                std::cout << ">> Wrong MMAP header for map '" << mapId << "': " << mmapTileFile << std::endl;
////                return false;
////            }
////
////            if (mmapTileHeader.mmapVersion < MMAP_VERSION)
////            {
////                std::cout << ">> Wrong MMAP version for map '" << mapId << "': " << mmapTileHeader.mmapVersion << " < " << MMAP_VERSION << std::endl;
////            }
////
////            void* mmapTileData = dtAlloc(mmapTileHeader.size, DT_ALLOC_PERM);
////            mmapTileStream.read(static_cast<char*>(mmapTileData), mmapTileHeader.size);
////            mmapTileStream.close();
////
////            dtTileRef tileRef;
////            dtStatus addTileStatus = NavMeshMap[mapId].second->addTile(static_cast<unsigned char*>(mmapTileData), mmapTileHeader.size, DT_TILE_FREE_DATA, 0, &tileRef);
////
////            if (dtStatusFailed(addTileStatus))
////            {
////                dtFree(mmapTileData);
////                dtFreeNavMesh(NavMeshMap[mapId].second);
////                std::cout << ">> Adding Tile to NavMesh for map '" << mapId << "' failed: " << addTileStatus << std::endl;
////                return false;
////            }
////        }
////    }
////
////    return true;
////}
//
//
//bool AmeisenNavigation::InitQueryAndLoadMmaps(int mapId)
//{
//    // we already have a query
//    if (mNavMeshQueryMap[mapId]) { return true; }
//
//    // we need to allocate a new query, but first check wheter we need to load a map or not
//    if (!LoadMmaps(mapId))
//    {
//        std::cout << ">> [" <<  "] Failed load MMAPs for map '" << mapId << "'" << std::endl;
//        return false;
//    }
//
//    // allocate and init the new query
//    m,SetNavmeshQuery(mapId, dtAllocNavMeshQuery());
//
//    if (!GetNavmeshQuery(mapId))
//    {
//        ANAV_ERROR_MSG(std::cout << ">> [" << "] Failed allocate NavMeshQuery for map '" << mapId << "'" << std::endl);
//        return false;
//    }
//
//    dtStatus initQueryStatus = GetNavmeshQuery(mapId)->init(NavMeshMap[mapId].second, MaxSearchNodes);
//
//    if (dtStatusFailed(initQueryStatus))
//    {
//        dtFreeNavMeshQuery(GetNavmeshQuery(mapId));
//        SetNavmeshQuery(mapId, nullptr);
//        std::cout << ">> [" << "] Failed to init NavMeshQuery for map '" << mapId << "': " << initQueryStatus << std::endl);
//        return false;
//    }
//
//    return true;
//}

bool AmeisenNavigation::CalculateNormalPath(int mapId, Vector3& startPosition, const Vector3& endPosition, Vector3* path, int* pathSize, dtPolyRef* visited)
{

    Vector3 startPositionRd = Vector3(startPosition);
    WowToRDCoords(startPositionRd);

    Vector3 endPositionRd = Vector3(endPosition);
    WowToRDCoords(endPositionRd);


    Vector3 closestPointStart;
    Vector3 closestPointEnd;

    dtPolyRef startPoly = GetNearestPoly(mapId, startPositionRd, &closestPointStart);
    dtPolyRef endPoly = GetNearestPoly(mapId, endPositionRd, &closestPointEnd);

    const std::unique_ptr<dtPolyRef> polypath(new dtPolyRef[maxPolyPath]);
    int polypathSize = 0;

    
    dtStatus polyPathStatus = mNavMeshQueryMap[mapId]->findPath(
        startPoly,
        endPoly,
        reinterpret_cast<const float*>(&closestPointStart),
        reinterpret_cast<const float*>(&closestPointEnd),
        &mQueryFilter,
        polypath.get(),
        &polypathSize,
        maxPolyPath
    );

   
    if (dtStatusSucceed(polyPathStatus))
    {
        std::cout << ">> [" << "] findPath: " << *pathSize << "/" << MaxPathNodes << std::endl;

        dtStatus straightPathStatus = mNavMeshQueryMap[mapId]->findStraightPath
        (
            reinterpret_cast<const float*>(&closestPointStart),
            reinterpret_cast<const float*>(&closestPointEnd),
            polypath.get(), polypathSize,
            reinterpret_cast<float*>(path),
            nullptr,
            visited,
            pathSize,
            maxPointPath * 3
        );



        if (dtStatusSucceed(straightPathStatus))
        {
            std::cout << ">> [" << "] findStraightPath: " << (*pathSize) << "/" << MaxPathNodes << std::endl;
            (*pathSize) *= 3;
            return true;
        }
        else
        {
           std::cout << ">> [" << "] Failed to call findStraightPath: " << straightPathStatus << std::endl;
        }
    }
    else
    {
        std::cout << ">> [" <<  "] Failed to call findPath: " << polyPathStatus << std::endl;
    }

    return false;
}


void AmeisenNavigation::SmoothPathCatmullRom(const float* input, int inputSize, float* output, int* outputSize, int points, float alpha) const noexcept
{
    InsertVector3(output, *outputSize, input, 0);

    // buffers to scale and add vectors
    float s0[3];
    float s1[3];

    float A1[3];
    float A2[3];
    float A3[3];

    float B1[3];
    float B2[3];

    float C[3];

    // make sure we dont go over the buffer bounds
    // why 3: we add 3 floats in the loop
    const int maxIndex = MaxPathNodes - 3;

    for (int i = 3; i < inputSize - 6; i += 3)
    {
        const float* p0 = input + i - 3;
        const float* p1 = input + i;
        const float* p2 = input + i + 3;
        const float* p3 = input + i + 6;

        const float t0 = 0.0f;

        const float t1 = std::powf(std::powf(p1[0] - p0[0], 2.0f) + std::powf(p1[1] - p0[1], 2.0f) + std::powf(p1[2] - p0[2], 2.0f), alpha * 0.5f) + t0;
        const float t2 = std::powf(std::powf(p2[0] - p1[0], 2.0f) + std::powf(p2[1] - p1[1], 2.0f) + std::powf(p2[2] - p1[2], 2.0f), alpha * 0.5f) + t1;
        const float t3 = std::powf(std::powf(p3[0] - p2[0], 2.0f) + std::powf(p3[1] - p2[1], 2.0f) + std::powf(p3[2] - p2[2], 2.0f), alpha * 0.5f) + t2;

        for (float t = t1; t < t2; t += ((t2 - t1) / static_cast<float>(points)))
        {
            ScaleAndAddVector3(p0, (t1 - t) / (t1 - t0), p1, (t - t0) / (t1 - t0), s0, s1, A1);
            ScaleAndAddVector3(p1, (t2 - t) / (t2 - t1), p2, (t - t1) / (t2 - t1), s0, s1, A2);
            ScaleAndAddVector3(p2, (t3 - t) / (t3 - t2), p3, (t - t2) / (t3 - t2), s0, s1, A3);

            ScaleAndAddVector3(A1, (t2 - t) / (t2 - t0), A2, (t - t0) / (t2 - t0), s0, s1, B1);
            ScaleAndAddVector3(A2, (t3 - t) / (t3 - t1), A3, (t - t1) / (t3 - t1), s0, s1, B2);

            ScaleAndAddVector3(B1, (t2 - t) / (t2 - t1), B2, (t - t1) / (t2 - t1), s0, s1, C);

            if (!std::isnan(C[0]) && !std::isnan(C[1]) && !std::isnan(C[2]))
            {
                if (*outputSize > maxIndex) { return; }

                InsertVector3(output, *outputSize, C, 0);
            }
        }
    }
}
void AmeisenNavigation::SmoothPathChaikinCurve(const float* input, int inputSize, float* output, int* outputSize) const noexcept
{
    InsertVector3(output, *outputSize, input, 0);

    // buffers to scale and add vectors
    float s0[3];
    float s1[3];

    float result[3];

    // make sure we dont go over the buffer bounds
    // why 9: we add 6 floats in the loop and 3 for the end position
    const int maxIndex = MaxPathNodes - 9;

    for (int i = 0; i < inputSize - 3; i += 3)
    {
        if (*outputSize > maxIndex) { break; }

        ScaleAndAddVector3(input + i, 0.75f, input + i + 3, 0.25f, s0, s1, result);
        InsertVector3(output, *outputSize, result, 0);

        ScaleAndAddVector3(input + i, 0.25f, input + i + 3, 0.75f, s0, s1, result);
        InsertVector3(output, *outputSize, result, 0);
    }

    InsertVector3(output, *outputSize, input, inputSize - 3);
}
