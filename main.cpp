#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "graphic.h"
#include "defs.h"
#include <vector>
#include <math.h>
using namespace std;
vector<SDL_Point> currentStroke;
bool isDrawing = false;
char convert_goc_to_huong(float angleDeg) {
    if (angleDeg < 0) angleDeg += 360.0f;

    if ((angleDeg >= 315 || angleDeg < 45))   return 'R';
    if (angleDeg >= 45 && angleDeg < 135)     return 'D';
    if (angleDeg >= 135 && angleDeg < 225)    return 'L';
    if (angleDeg >= 225 && angleDeg < 315)    return 'U';

    return '?';
}

string convert_huong_to_string(const std::vector<SDL_Point>& points) {
    char lastDir;
    string result;
  for (size_t i = 1; i < points.size(); ++i) {
    int dx = points[i].x - points[i - 1].x;
    int dy = points[i].y - points[i - 1].y;

    float distance = sqrt(dx * dx + dy * dy);
    if (distance < 10) continue; // Bỏ qua đoạn quá ngắn (lọc nhiễu)

    float angleRad = std::atan2(dy, dx);
    float angleDeg = angleRad * (180.0f / M_PI);
    char dir = convert_goc_to_huong(angleDeg);

    if (dir != lastDir) {
        result += dir;
        lastDir = dir;
    }
}
return result;
}
void cbi_ghi_nhan() {
    currentStroke.clear();
}
void ghi_nhan_vecto_diem() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (currentStroke.empty() ||
        (abs(x - currentStroke.back().x) + abs(y - currentStroke.back().y)) >= 6) {
        currentStroke.push_back({x, y});
    }
}

char kiem_tra_so_khop(const vector<SDL_Point>& stroke) {
    string a = convert_huong_to_string(stroke);
    if(a.length() >= 6 && a[0] == 'D' && a[1] == 'U' && a[2] == 'D' && a[3] == 'U' && a[4] == 'D' && a[5] == 'U') return '#';
    if(a.length() >= 2 && a[0] == 'D' && a[1] == 'U') return 'v';
    if(a.length() >= 3 && a[0] == 'R' && a[1] == 'D' || a[1] == 'L' && a[2] == 'R') return 'z';
    if(a.length() == 1 && a[0] == 'U' || a[0] == 'D') return 'i';
    if(a.length() >= 7 && a[0] == 'R' && a[a.length()-1] == 'R' ){
       int countdownonce= 0;
       for(int i = 2 ;  i < a.length() - 2;  i++ ){
        if(a[i] == 'D') countdownonce++;
        if( countdownonce == 1&& i == a.length() - 3) return 'f' ;
       }}
        if(a.length() >= 4){
            int has_L = 0;
            int has_D = 0;
            int has_R = 0;
            int has_U = 0;
            if(a.length() >= 7 && a[0] == 'U' && a[a.length()-1] =='D'){
       int countaccept = 0;
        for(int i = 2 ;  i < a.length() - 2;  i++ ){
            if(a[i] == 'R') countaccept++;
            if( countaccept == 1&& i == a.length() - 3)return  'p' ;
        }
       }
        for(int i =0 ; i < a.length() ; i++){
            if((a[i] == 'L') && has_L == 0) has_L = i;
            if((a[i] == 'D') && has_D == 0) has_D = i;
            if((a[i] == 'R') && has_R == 0) has_R = i;
            if((a[i] == 'U') && has_U == 0) has_U = i;
            if( has_L* has_D *has_R * has_U  ) return 'o';
        }
    }

       return 'x';
}


void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}


int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();

    SDL_Rect rect;
    rect.x = 100;
    rect.y = 100;
    rect.h = 100;
    rect.w = 100;
    SDL_SetRenderDrawColor(graphics.renderer, 155, 255, 155, 0);
    SDL_RenderFillRect(graphics.renderer, &rect);
    SDL_RenderPresent(graphics.renderer);

    SDL_Rect rect2;
    rect2.x = 150;
    rect2.y = 150;
    rect2.h = 100;
    rect2.w = 100;
    SDL_SetRenderDrawColor(graphics.renderer, 155, 155, 255, 0);
    SDL_RenderFillRect(graphics.renderer, &rect2);
    SDL_RenderPresent(graphics.renderer);

    SDL_Event event;
    int x, y;

    while (true) {
        SDL_GetMouseState(&x, &y);

        // Nếu đang giữ chuột, ghi nhận điểm liên tục
        if (isDrawing) {
            ghi_nhan_vecto_diem();
        }

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    graphics.quit();
                    exit(0);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    cbi_ghi_nhan();
                    ghi_nhan_vecto_diem();
                    isDrawing = true;
                    break;
                case SDL_MOUSEBUTTONUP:
                    isDrawing = false;
                    char ans;
                    ans = kiem_tra_so_khop(currentStroke);
                    cerr << ans <<endl;
                    break;
            }
        }

        SDL_Delay(16);
    }

    graphics.quit();
    return 0;
}
