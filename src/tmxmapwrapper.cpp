#include "tmxmapwrapper.hpp"
#include <xd/xd.hpp>
#include <libgen.h>

using namespace xd;

TmxMapWrapper::TmxMapWrapper(const string& filename) {
    tmxmap = new Tmx::Map();
    tmxmap->ParseFile(filename);

    auto tmxBackgroundColor = tmxmap->GetBackgroundColor();
    backgroundColor = vec4(tmxBackgroundColor.GetRed() / 255.0f, tmxBackgroundColor.GetGreen() / 255.0f, tmxBackgroundColor.GetBlue() / 255.0f, tmxBackgroundColor.GetAlpha() / 255.0f);

    for (auto tileset : tmxmap->GetTilesets()) {
        auto tmxImage = tileset->GetImage();
        char* tmp = strdup(filename.c_str());
        auto xdImage = loadImage(string(dirname(tmp)) + "/" + tmxImage->GetSource());
        delete tmp;
        images.push_back(xdImage);
        Spritesheet* spritesheet = new Spritesheet(xdImage, tileset->GetColumns(), tileset->GetTileCount() / tileset->GetColumns());
        spritesheets.push_back(spritesheet);

        for (auto tile : tileset->GetTiles()) {
            if (tile->IsAnimated()) {
                vector<Sprite> frames;
                int frameDuration = 0;
                for (auto frame : tile->GetFrames()) {
                    frames.push_back(spritesheet->sprites[frame.GetTileID()]);
                    frameDuration = frame.GetDuration();
                }
                animations[make_pair(spritesheets.size() - 1, tile->GetId())] = new Animation(frames, frameDuration, 0, 0);
            }
        }
    }
}

TmxMapWrapper::~TmxMapWrapper() {
    delete tmxmap;
    images.clear();
    spritesheets.clear();
}

void TmxMapWrapper::draw() {
    background(backgroundColor);
    for (auto tileLayer : tmxmap->GetTileLayers()) {
        for (int y = 0; y < tileLayer->GetHeight(); y++) {
            for(int x = 0; x < tileLayer->GetWidth(); x++) {
                if (tileLayer->GetTileTilesetIndex(x, y) > -1) {
                    auto mapTile = tileLayer->GetTile(x, y);
                    int tilesetId = mapTile.tilesetId;
                    auto tileset = tmxmap->GetTileset(tilesetId);
                    int tileWidth = tileset->GetTileWidth();
                    int tileHeight = tileset->GetTileHeight();
                    int tileId = mapTile.id;
                    auto tile = tileset->GetTile(tileId);
                    if (tile && tile->IsAnimated()) {
                        animations[make_pair(tilesetId, tileId)]->draw(x * tileWidth, y * tileHeight, tileWidth, tileHeight, mapTile.flippedHorizontally, mapTile.flippedVertically, mapTile.flippedDiagonally);
                    } else {
                        spritesheets[tilesetId]->sprites[tileId].draw(x * tileWidth, y * tileHeight, tileWidth, tileHeight, mapTile.flippedHorizontally, mapTile.flippedVertically, mapTile.flippedDiagonally);
                    }
                }
            }
        }
    }
}