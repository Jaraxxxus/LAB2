#pragma once
#include <windows.h>
#include <string>

/*
#define WORLD_H 10
#define WORLD_W 10
*/

class konvey {

private:
    int step;
    char** wrd;
    char** old_wrd;
    //friend std::ostream& operator<<(std::ostream& os, const konvey & game);

public:
    konvey();
    ~konvey();
    void clr_world();
    int get_live_count();
    void read_point_neighbors(int nb[][2], int x, int y);
    int count_live_neighbors(int x, int y);
    void swap_world();
    int cmp_world();
    char get_world( int x,  int y);
    char get_old( int x, int y);
    void next_generation();
    void set_pos( int x,  int y);
    void set_dot( int x,  int y);
    char* get_world_str( int x);
    int get_step();
    void set_step(int x);
};


class CSScreenException {
public:
    CSScreenException(int _err) : err(_err) {}
    const char* what();
    int err;
};


class CScreen {
public:
    CScreen();
    ~CScreen();
    void cursor_show(bool visible);
    void text_attr(WORD attr);
    void pos(int x, int y, char ch = 0);
    void pos_str(int x, int y, const char* str);
    void cls();

private:
    HANDLE hConsoleOutput;
    CONSOLE_CURSOR_INFO oldCursorInfo, curCursorInfo;
    WORD oldTextAttr;
};



class Command
{
private:
    
public:
    //	Command();
    //   ~Command();
   // void playGame(CScreen screen);
    void print_world(CScreen screen, konvey& wrd);
    void set_comm(CScreen screen);
    int sTOi(std::string str);
    void saveF(const std::string fileName, konvey& wrd) const;
    int loadF(const std::string fileName, konvey& wrd);
    friend std::ostream& operator<<(std::ostream& os, konvey& wrd);
    void playTest();
};
