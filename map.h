#ifndef MAP_MODULE_H
#define MAP_MODULE_H

#define MAP_W 10
#define MAP_H 10
#define TILE 48

int MapIsWallAt(float x ,float y);
int MapIsInside(float x,float y);
int MapCircleCollides(float x,float y,float r);
int MapGetCell(int x,int y);
void MapSetCell(int x, int y, int value);
void MapSaveToFile(const char* filename);
void MapLoadFromFile(const char* filename);
void Draw2DMap(void);


#endif 