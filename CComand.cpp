
//#include <cstring>
#include <fstream>
#include <string>
#include <iostream>
#include <conio.h>
#include "HeadLab2.h"

//#include "CScreen.h"


#define WORLD_H 10
#define WORLD_W 10

//konvey The_wrd;
/*
void Command:: set_comm(CScreen screen)
{  screen.pos_str(9, 14, "                          ");	
}*/
  //------

std::ostream& operator<<(std::ostream& os, konvey& wrd){
    for (int i = 0; i < WORLD_H; i++){
        for (int j = 0; j < WORLD_W; j++){
            std::cout << wrd.get_world(i,j) ;
        }
        std::cout << "\n";
    }
    return os;
}

void Command::saveF(const std::string fileName, konvey &wrd) const{
    std::ofstream file(fileName.c_str());//   (fileName+ ".txt"	);
    
	file.clear();
    for (int i = 0; i < WORLD_H; i++){
        for (int j = 0; j < WORLD_W; j++){
            file << wrd.get_world(i,j);
        }
        file << "\n";
    }
    file << wrd.get_step();
    file << std::endl;
    file.close();
    
}


int Command::loadF(const std::string fileName, konvey &wrd){
    std::ifstream file(fileName.c_str());
    char ch;
    
	for (unsigned int i = 0; i < WORLD_H; i++){
        for (unsigned int j = 0; j < WORLD_W; j++){
            file >> ch; 
			if (ch == '*')
			  wrd.set_pos(i,j) ;
			else if (ch == '.')
			  wrd.set_dot(i,j) ;
        }
    }
    file >> ch ;  
	int nStep=  (int) (ch-'0');
    //wrd.set_step((int) (ch-'0'));
    file.close();
    return nStep;

}

int Command:: sTOi(std::string str){
int res = 0;	

	for (unsigned int i = 0; i < str.length(); i++){
		if (str[i] == '\n')
		  break;
		else 
		  res = res * 10+ (int) (str[i] - '0');
		 
	}
	return res;
}

void Command::print_world(CScreen screen, konvey &wrd){
  /*  unsigned int i, j;
    screen.pos(1, 2);
    char ch;
    for (i = 0; i < WORLD_W; i++) {
        for (j = 0; j < WORLD_H; j++) {
          
		  ch = wrd.get_world(i, j) ;
          screen.pos(1+j, 2+i, ch);
       }
    }
	screen.pos_str(20 , 1, "                  ");
//	ch = '0'+ (char) wrd.get_step();
	screen.pos(20, 1);  
	_cprintf("%d", wrd.get_step());    */
}


/*
void Command::playGame(CScreen screen) {
        
        int j;
        char ch;
        konvey The_wrd;
        The_wrd.clr_world();
        screen.pos_str(0, 0, "KONVEY LIFE,  WELCOME "); 
	    screen.pos_str(1, 1, "0123456789    step" );
        //screen.pos(0, 2);
        for(int i = 0; i < WORLD_W; i++)
        {        	
        	screen.pos(0,2+i, (char)(i+65) );
        	for (j = 0; j < WORLD_H; j++) {
          
		     ch = The_wrd.get_world(i, j) ;
             screen.pos(1+j, 2+i, ch);
            }
        	
        }
        
		
        unsigned int live_points = -1;
        bool is_optimal = false;

        
        The_wrd.set_pos(0,0);
	    The_wrd.set_pos(1,1);
		The_wrd.set_pos(0,2);
		The_wrd.set_pos(1,3);
		The_wrd.set_pos(2,1);
		The_wrd.set_pos(3,0);
		The_wrd.set_pos(2,9);
		The_wrd.set_pos(1,9);
		The_wrd.set_pos(2,3);
		The_wrd.set_pos(3,3);
       // print_world(screen, The_wrd);

        
        screen.pos_str(1, 13, "set, step, reset, clear, back, save, load, end");

        screen.pos_str(1, 14, "Command:_");
        //screen.cursor_show(true);
        
//--------------выделить отдельно в функцию
        int DoGame = 1;
        std::string input;
        while (DoGame == 1){
        	screen.pos(10, 14); 
            screen.cursor_show(true);
            getline(std::cin,input);
            screen.cursor_show(false);
            screen.pos(10, 14);
            if (input == "reset"){             
              The_wrd.clr_world();
              print_world(screen, The_wrd);  
			  
        } else if (input.substr(0,3) == "set"){
        	The_wrd.set_pos(input[3] - 'A',input[4] - '0');
			print_world(screen, The_wrd);  
        } else if (input.substr(0,5) == "clear"){
            The_wrd.set_dot(input[5] - 'A',input[6] - '0');
            
            print_world(screen, The_wrd);  
            //set_comm(screen);       
         
        } else if (input.substr(0,4) == "step"){
        	
            if (input.length() == 4) {
              The_wrd.next_generation();
              The_wrd.set_step(The_wrd.get_step()+1);  
			  print_world(screen, The_wrd);
			  if (The_wrd.get_step() >0)
		         is_optimal = The_wrd.cmp_world() == 0;
              live_points = The_wrd.get_live_count();

              if (is_optimal) {
              	screen.pos_str(1, 15, "Optimal configuration detected");
                break;
              }

              if (live_points == 0) {
              	 screen.pos_str(1, 15, "All points died");
                 break;
              }
              The_wrd.swap_world();}
            else {
                int N = sTOi(input.substr(4));
                screen.pos(16, 16); 
                for (j = 0; j < N; j++){
                    The_wrd.next_generation();
                    The_wrd.set_step(The_wrd.get_step()+1);
                    print_world(screen, The_wrd);
                    if (The_wrd.get_step() >0)
		              is_optimal = The_wrd.cmp_world() == 0;
                    live_points = The_wrd.get_live_count();

                    if (is_optimal) {
              	      screen.pos_str(1, 15, "Optimal configuration detected");
                      break;
                    }

                    if (live_points == 0) {
              	      screen.pos_str(1, 15, "All points died");
                      break;
                    }
                The_wrd.swap_world();
             
                }
            }
       } else if (input.substr(0,4) == "back"){
            The_wrd.swap_world();
            The_wrd.set_step(The_wrd.get_step()-1);            
            print_world(screen, The_wrd); 


        } else if (input.substr(0,4) == "save"){      
            std::string fileName = input.substr(4);
            saveF(fileName, The_wrd);
        } else if (input.substr(0,4) == "load"){
            std::string fileName = input.substr(4);
            int nStep;
            nStep = loadF(fileName, The_wrd);
            The_wrd.set_step(nStep); 
            print_world(screen, The_wrd);  
        } else if (input == "end"){
            DoGame = 0;
            break;
        }
          
		set_comm(screen); 

}
	}*/
        
    void Command::playTest() {

        int j;
        char ch;
        konvey The_wrd;
        

        unsigned int live_points = -1;
        bool is_optimal = false;

//--------------выделить отдельно в функцию
        int DoGame = 1;
        std::string input;
        while (DoGame == 1) {
            
            getline(std::cin, input);
            
            if (input == "reset") {
                The_wrd.clr_world();
               

            }
            else if (input.substr(0, 3) == "set") {
                The_wrd.set_pos(input[3] - 'A', input[4] - '0');
               
            }
            else if (input.substr(0, 5) == "clear") {
                The_wrd.set_dot(input[5] - 'A', input[6] - '0');

                
            }
            else if (input.substr(0, 4) == "step") {

                if (input.length() == 4) {
                    The_wrd.next_generation();
                    The_wrd.set_step(The_wrd.get_step() + 1);
                  
                    if (The_wrd.get_step() > 0)  is_optimal = The_wrd.cmp_world() == 0;
                    live_points = The_wrd.get_live_count();

                    if (is_optimal) {
                       
                        break;
                    }

                    if (live_points == 0) {
                        
                        break;
                    }
                    The_wrd.swap_world();
                }
                else {
                    int N = sTOi(input.substr(4));
                   
                    for (j = 0; j < N; j++) {
                        The_wrd.next_generation();
                        The_wrd.set_step(The_wrd.get_step() + 1);
                        
                        if (The_wrd.get_step() > 0)
                            is_optimal = The_wrd.cmp_world() == 0;
                        live_points = The_wrd.get_live_count();

                        if (is_optimal) {
                           
                            break;
                        }

                        if (live_points == 0) {
                           
                            break;
                        }
                        The_wrd.swap_world();

                    }
                }
            }
            else if (input.substr(0, 4) == "back") {
                The_wrd.swap_world();
                The_wrd.set_step(The_wrd.get_step() - 1);


            }
            else if (input.substr(0, 4) == "save") {
                std::string fileName = input.substr(4);
                saveF(fileName, The_wrd);
            }
            else if (input.substr(0, 4) == "load") {
                std::string fileName = input.substr(4);
                int nStep;
                nStep = loadF(fileName, The_wrd);
                The_wrd.set_step(nStep);
                
            }
            else if (input == "end") {
                DoGame = 0;
                break;
            }

        }
    }