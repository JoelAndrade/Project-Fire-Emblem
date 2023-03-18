#ifndef SDL_CLASSES_H
#define SDL_CLASSES_H

#include <iostream>
#include <string.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define PI (3.1415)      
#define DEG_TO_RAD(deg) (deg * (2.0*PI/360))

#define RENDERCOLOR 0, 0, 0, 0xFF // black background
//#define renderColor 255, 255, 255, 0xFF // white background

class win {
    public:
        int w;
        int h;
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;
        SDL_Color renderColor = {RENDERCOLOR};

        win() {}
        win(int widthVal, int heightVal, const char* title = "No Title", SDL_WindowFlags flag = SDL_WINDOW_SHOWN) {
            w = widthVal;
            h = heightVal;
            window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flag);
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            SDL_SetRenderDrawColor(renderer, renderColor.r, renderColor.g, renderColor.b, renderColor.a);
        }

        void init(int widthVal, int heightVal, const char* title = "No Title", SDL_WindowFlags flag = SDL_WINDOW_SHOWN) {
            w = widthVal;
            h = heightVal;
            window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flag);
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            SDL_SetRenderDrawColor(renderer, renderColor.r, renderColor.g, renderColor.b, renderColor.a);
        }

        void setWindowSize(int widthVal, int heightVal) {
            w = widthVal;
            h = heightVal;
            SDL_SetWindowSize(window, w, h);
        }

        void getWindowSize(void) {
            SDL_GetWindowSize(window, &w, &h);
        }

        void setWindowPos(int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED) {
            SDL_SetWindowPosition(window, x, y);
        }

        SDL_Texture* createSurfaceTexture(int widthVal, int heightVal, int r = 255, int g = 255, int b = 255, int a = 0xFF) {
            SDL_Surface* surface = SDL_CreateRGBSurface(0, widthVal, heightVal, 32, 0, 0, 0, 0);
            SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, r, g, b, a));
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            
            SDL_FreeSurface(surface);
            return texture;
        }
        
        void clearRender(void) {
            SDL_SetRenderDrawColor(renderer, renderColor.r, renderColor.g, renderColor.b, renderColor.a);
            SDL_RenderClear(renderer);
        }

        void drawLine(int x1, int y1, int x2, int y2, SDL_Color* color, int xScale = 1, int yScale = 1) { // TODO: Might want to change the parameters to take to point types
            if (color == NULL) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            else {
                SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
            }
            if (xScale < 1) {
                xScale = 1;
            }
            if (yScale < 1) {
                yScale = 1;
            }

            xScale -= 1;
            yScale -= 1;

            x1 = x1 - xScale;
            y1 = y1 - yScale;
            x2 = x2 - xScale;
            y2 = y2 - yScale;

            for (int i = 0; x1 - xScale + i < x1 + xScale + 1; ++i) {
                for (int j = 0; y1 - yScale + j < y1 + yScale + 1; ++j) {
                    SDL_RenderDrawLine(renderer, x1 + i, y1 + j, x2 + i, y2 + j);
                }
            }            
        }
        void drawLines(SDL_Point* points, SDL_Color* color, int numPoints, int xScale = 1, int yScale = 1) {
            if (color == NULL) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            else {
                SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
            }
            if (xScale < 1) {
                xScale = 1;
            }
            if (yScale < 1) {
                yScale = 1;
            }

            xScale -= 1;
            yScale -= 1; 

            for (int i = 0; i < numPoints; ++i) {
                points[i].x -= xScale;
                points[i].y -= yScale;
            }

            for (int i = 0; points[0].x - xScale + i < points[0].x + xScale + 1; ++i) {
                for (int i = 0; points[0].y - yScale + i < points[0].y + yScale + 1; ++i) {
                    SDL_RenderDrawLines(renderer, points, numPoints);
                    for (int j = 0; j < numPoints; ++j) {
                        ++points[j].y;
                    }
                }
                for (int j = 0; j < numPoints; ++j) {
                    points[j].y -=  (2*yScale) + 1;
                    ++points[j].x;
                }
            }

            for (int i = 0; i < numPoints; ++i) {
                points[i].x -= xScale + 1;
                points[i].y += yScale;
            }
        }

        void drawRect(SDL_Color* color, SDL_Rect rect, int xScale = 1, int yScale = 1) {
            if (color == NULL) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            else {
                SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
            }
            if (xScale < 1) {
                xScale = 1;
            }
            if (yScale < 1) {
                yScale = 1;
            }

            xScale -= 1;
            yScale -= 1;

            SDL_Rect tempRect = rect;
            tempRect.x = tempRect.x - xScale;
            tempRect.y = tempRect.y - yScale;
            for (int i = 0; rect.x - xScale + i < rect.x + xScale + 1; ++i) {
                SDL_RenderDrawRect(renderer, &tempRect);
                ++tempRect.x;
            }
            tempRect = rect;
            tempRect.x = tempRect.x - xScale;
            tempRect.y = tempRect.y - yScale;            
            for (int i = 0; rect.y - yScale + i < rect.y + yScale + 1; ++i) {
                SDL_RenderDrawRect(renderer, &tempRect);
                ++tempRect.y;
            }
            tempRect = rect;
            tempRect.x = tempRect.x + xScale;
            tempRect.y = tempRect.y + yScale;            
            for (int i = 0; rect.y - yScale - 1 < rect.y + yScale + i; --i) {
                SDL_RenderDrawRect(renderer, &tempRect);
                --tempRect.y;
            }
        }
        void drawRect(SDL_Color* color, int xScale = 1, int yScale = 1) {
            if (color == NULL) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            else {
                SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
            }
            if (xScale < 1) {
                xScale = 1;
            }
            if (yScale < 1) {
                yScale = 1;
            }

            SDL_RenderSetScale(renderer, xScale, yScale);
            SDL_RenderDrawRect(renderer, NULL);
            SDL_RenderSetScale(renderer, 1, 1);
        }

        void fillRect(SDL_Color* color, SDL_Rect rect, int xScale = 1, int yScale = 1) {
            if (color == NULL) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            else {
                SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
            }
            rect.w = rect.w + 1;
            rect.h = rect.h + 1;
            SDL_RenderFillRect(renderer, &rect);
        }
        void fillRect(SDL_Color* color, float xScale = 1, float yScale = 1) {
            if (color == NULL) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            else {
                SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
            }
            SDL_RenderSetScale(renderer, xScale, yScale);
            SDL_RenderFillRect(renderer, NULL);
            SDL_RenderSetScale(renderer, 1, 1);
        }

        void drawCircle(SDL_Point center, SDL_Color* color, int radius, int scale = 1, double increments = 1) {

            if (color == NULL) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            else {
                SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
            }
            if (scale < 1) {
                scale = 1;
            }

            int x;
            int y;

            SDL_Point previousPoint = {radius, 0};
            for (double theta = 0; theta < 360; theta = theta + increments) {
                x = round(radius*cos(DEG_TO_RAD(theta)));
                y = round(radius*sin(DEG_TO_RAD(theta)));

                drawLine(center.x + previousPoint.x, center.y - previousPoint.y, center.x + x, center.y - y, color, scale, scale);

                previousPoint.x = x;
                previousPoint.y = y;
            }
            
        }
};

class textureImage {
    public:
        SDL_Texture* texture = NULL;
        SDL_Rect originalRect;
        SDL_Rect newRect;

        textureImage() {}
        textureImage(SDL_Renderer* renderer, const char* path, double scaleImage = 1.0, int xPos = 1, int yPos = 1) {
            SDL_Surface* imageSurface = IMG_Load(path);
            texture = SDL_CreateTextureFromSurface(renderer, imageSurface);

            originalRect.x = 0;
            originalRect.y = 0;
            originalRect.w = imageSurface->w;
            originalRect.h = imageSurface->h;
            originalRect.makeDimensions();
            newRect.x = xPos;
            newRect.y = xPos;
            newRect.w = imageSurface->w * scaleImage;
            newRect.h = imageSurface->h * scaleImage;
            newRect.makeDimensions();
                        
            SDL_FreeSurface(imageSurface);
        }
        textureImage(SDL_Renderer* renderer, const char* path, int widthVal, int heightVal, int xPos = 0, int yPos = 0) {
            SDL_Surface* imageSurface = IMG_Load(path);
            texture = SDL_CreateTextureFromSurface(renderer, imageSurface);

            originalRect.x = 0;
            originalRect.y = 0;
            originalRect.w = imageSurface->w;
            originalRect.h = imageSurface->h;
            originalRect.makeDimensions();
            newRect.x = xPos;
            newRect.y = yPos;
            newRect.w = widthVal;
            newRect.h = heightVal;
            newRect.makeDimensions();

            SDL_FreeSurface(imageSurface);
        }
        textureImage(SDL_Renderer* renderer, SDL_Color color, int widthVal, int heightVal, int xPos = 0, int yPos = 0) {
            SDL_Surface* surface = SDL_CreateRGBSurface(0, widthVal, heightVal, 32, 0, 0, 0, 0);
            SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            blend(SDL_BLENDMODE_BLEND);

            originalRect.x = 0;
            originalRect.y = 0;
            originalRect.w = surface->w;
            originalRect.h = surface->h;
            originalRect.makeDimensions();
            newRect.x = xPos;
            newRect.y = yPos;
            newRect.w = widthVal;
            newRect.h = heightVal;
            newRect.makeDimensions();
            
            SDL_FreeSurface(surface);
        }

        void init(SDL_Renderer* renderer, const char* path, double scaleImage = 1.0, int xPos = 0, int yPos = 0) {
            SDL_Surface* imageSurface = IMG_Load(path);
            texture = SDL_CreateTextureFromSurface(renderer, imageSurface);

            originalRect.x = 0;
            originalRect.y = 0;
            originalRect.w = imageSurface->w;
            originalRect.h = imageSurface->h;
            originalRect.makeDimensions();
            newRect.x = xPos;
            newRect.y = yPos;
            newRect.w = imageSurface->w * scaleImage;
            newRect.h = imageSurface->h * scaleImage;
            newRect.makeDimensions();
                        
            SDL_FreeSurface(imageSurface);
        }
        void init(SDL_Renderer* renderer, const char* path, int widthVal, int heightVal, int xPos = 0, int yPos = 0) {
            SDL_Surface* imageSurface = IMG_Load(path);
            texture = SDL_CreateTextureFromSurface(renderer, imageSurface);

            originalRect.x = 0;
            originalRect.y = 0;
            originalRect.w = imageSurface->w;
            originalRect.h = imageSurface->h;
            originalRect.makeDimensions();
            newRect.x = xPos;
            newRect.y = yPos;
            newRect.w = widthVal;
            newRect.h = heightVal;
            newRect.makeDimensions();

            SDL_FreeSurface(imageSurface);
        }
        void init(SDL_Renderer* renderer, SDL_Color color, int widthVal, int heightVal, int xPos = 0, int yPos = 0) {
            SDL_Surface* surface = SDL_CreateRGBSurface(0, widthVal, heightVal, 32, 0, 0, 0, 0);
            SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            blend(SDL_BLENDMODE_BLEND);

            originalRect.x = 0;
            originalRect.y = 0;
            originalRect.w = surface->w;
            originalRect.h = surface->h;
            originalRect.makeDimensions();
            newRect.x = xPos;
            newRect.y = yPos;
            newRect.w = widthVal;
            newRect.h = heightVal;
            newRect.makeDimensions();
            
            SDL_FreeSurface(surface);
        }

        void reSize(int wVal, int hVal) {
            newRect.w = wVal;
            newRect.h = hVal;
            newRect.makeDimensions();
        }

        void changePos(int xPos, int yPos) {
            newRect.x = xPos;
            newRect.y = yPos;
            newRect.makeDimensions();
        }

        void changePosAndSize(int wVal, int hVal, int xPos, int yPos) {
            newRect.x = xPos;
            newRect.y = yPos;
            newRect.w = wVal;
            newRect.h = hVal;
            newRect.makeDimensions();
        }

        void render(SDL_Renderer* renderer) {
            SDL_RenderCopy(renderer, texture, &originalRect, &newRect);
        }

        void renderRotate(SDL_Renderer* renderer, double angle, SDL_Point* center = NULL) {
            SDL_RenderCopyEx(renderer, texture, &originalRect, &newRect, angle, center, SDL_FLIP_NONE);
        }

        void renderFlip(SDL_Renderer* renderer, SDL_RendererFlip flip) {
            SDL_RenderCopyEx(renderer, texture, &originalRect, &newRect, 0.0, NULL, flip);
        }

        void setAlpha(Uint8 alpha) {
            SDL_SetTextureAlphaMod(texture, alpha);
        }

        void blend(SDL_BlendMode blendMode) {
            SDL_SetTextureBlendMode(texture, blendMode);
        }

        void destroy(void) {
            SDL_DestroyTexture(texture);
        }
};

class textureText {
    public:
        TTF_Font* font = NULL;
        SDL_Texture* texture = NULL;
        SDL_Rect rect;
        SDL_Color color = {0, 0, 0, 0xFF};
        int fontSize = 10;
        const char* path = NULL;
        std::string text = "";

        textureText() {}
        textureText(SDL_Renderer* renderer, const char* pathInput, const char* textInput, int fontSizeVal, int xPos = 0, int yPos = 0) {
            text = textInput;
            fontSize = fontSizeVal;
            path = pathInput;
            font = TTF_OpenFont(path, fontSize);                
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
            texture = SDL_CreateTextureFromSurface(renderer, textSurface);

            rect.x = xPos;
            rect.y = yPos;
            if (text != "") {
                rect.w = textSurface->w;
                rect.h = textSurface->h;
                rect.makeDimensions();
            }

            SDL_FreeSurface(textSurface);
        }

        void init(SDL_Renderer* renderer, const char* pathInput, const char* textInput, int fontSizeVal, int xPos = 0, int yPos = 0) {
            text = textInput;
            fontSize = fontSizeVal;
            path = pathInput;
            font = TTF_OpenFont(path, fontSize);
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
            texture = SDL_CreateTextureFromSurface(renderer, textSurface);

            rect.x = xPos;
            rect.y = yPos;
            if (text != "") {
                rect.w = textSurface->w;
                rect.h = textSurface->h;
                rect.makeDimensions();
            }

            SDL_FreeSurface(textSurface);
        }

        void reSize(int fontSizeVal) {
            if (font != NULL) {
                fontSize = fontSizeVal;
                font = TTF_OpenFont(path, fontSize);
                SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
                
                if (text != "") {
                    rect.w = textSurface->w;
                    rect.h = textSurface->h;
                    rect.makeDimensions();
                }

                SDL_FreeSurface(textSurface);
            }
            else {
                std::cout << "Font is NULL" << std::endl;
            }
        }

        void changePos(int xPos, int yPos) {
            rect.x = xPos;
            rect.y = yPos;
            rect.makeDimensions();
        }

        void changePosAndSize(int fontSizeVal, int xPos, int yPos) {
            if (font != NULL) {
                fontSize = fontSizeVal;
                font = TTF_OpenFont(path, fontSize);
                SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
                
                rect.x = xPos;
                rect.y = yPos;
                if (text != "") {
                    rect.w = textSurface->w;
                    rect.h = textSurface->h;
                    rect.makeDimensions();
                }

                SDL_FreeSurface(textSurface);
            }
            else {
                std::cout << "Font is NULL" << std::endl;
            }
        }

        void render(SDL_Renderer* renderer) {
            SDL_RenderCopy(renderer, texture, NULL, &rect);
        }

        void createTexture(SDL_Renderer* renderer) {
            if (font != NULL) {
                SDL_DestroyTexture(texture);
                SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
                texture = SDL_CreateTextureFromSurface(renderer, textSurface);
                
                if (text != "") {
                    rect.w = textSurface->w;
                    rect.h = textSurface->h;
                    rect.makeDimensions();
                }

                SDL_FreeSurface(textSurface);
            }
            else {
                std::cout << "Font is NULL" << std::endl;
            }
        }

        void changeColor(SDL_Color* colorVal) {
            color.r = colorVal->r;
            color.g = colorVal->g;
            color.b = colorVal->b;
            color.a = colorVal->a;
        }

        void changeFont(const char* pathVal) {
            font = NULL;
            path = pathVal;
            font = TTF_OpenFont(path, fontSize);
        }

        void destroy(void) {
            SDL_DestroyTexture(texture);
            TTF_CloseFont(font);
        }
};

#endif // SDL_CLASSES_H
