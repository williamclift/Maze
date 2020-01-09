/*
    William Clift
    2 Decemeber 2019
    Object-Oriented Design
    Maze Project
*/

#ifndef Maze_H_
#define Maze_H_

#include <iostream>
#include "Maze.h"
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
using namespace std;

int main(){
    srand(time(0));                 //Set the time for the random function
    int size = 0;                   // The size of the maze Grid
    bool valid = false;
    while(!valid){
        cout << "Set Size (1-15): ";        //Mazes larger than about 15 get very slow
        cin >> size;
        if(size < 2){
            cout << "Invalid Size" << endl;
        } else{
            valid = true;
        }
    }

    Maze * m;
    m = new Maze(size);
    m->createMaze();
    cout << m->solveE() << endl;
    
    m->deleteMaze();
    return 0;
}
/**
 Constructor for the Maze class of objects
 @param int n - the size of the desired grid
 */
Maze::Maze(int n){
    this->n = n;                            // Initial Size
    this->cpi = 0;                          // Current Row      Position
    this->cpj = 0;                          // Current Column   Position
    this->endMaze = false;                  //boolean to determine when to end the maze
}

/**
 To delete the maze array at the end of running the program
 */
void Maze::deleteMaze(){
    for(int i = 0; i< n; i++){
        delete [] maze[i];                  // Delete the maze array
    }
}

/**
 Setting the size of the grid after initializing, but before creating the maze.
 @param int size - the new desired size of the array.
 */
void Maze::setSize(int size){
    this->n = size;
    cout << "Size changed to " << n << std::endl;
}

/**
 The method to create the maze.
 */
void Maze::createMaze(){
    this-> maze = new int*[this->n];
    
    for(int i= 0; i < n; i++){              // Fill in the initial array with 0's
        maze[i] = new int[n];
        for(int j = 0; j < n; j++){
            maze[i][j] = 0;                 // Each element is 0.
        }
    }
    makePath();                             // Put 1's in each tunnel space , 0's are walls
}

/**
 Make the path for the maze - puts 1's in all spaces acting as tunnels.
 */
void Maze::makePath(){
    this->endMaze = false;
    
    maze[0][0] = 1;
    
    while(!endMaze){
        if(cpi == n-1)                      // Ends the Maze path at the bottom line
            endMaze = true;
        selectMove();    // 0-3
    }
    cout << "Tunnels formed." << std::endl;
    toString();
    cout << "Done." << std::endl;
}

/**
 Performing the move for creating the tunnel
 @param int move - the suggested move to place the next 1 for the tunnel
 */
void Maze::makeMove(int move){
    if(move == 0){                          // Move Right
        cpj++;
        maze[cpi][cpj] = 1;
    }
    else if(move == 1){                     // Move Up
        cpi--;
        maze[cpi][cpj] = 1;
    }
    else if(move == 2){                     // Move Left
        cpj--;
        maze[cpi][cpj] = 1;
    }
    else if(move == 3){                     // Move Down
        cpi++;
        maze[cpi][cpj] = 1;
    }
}

/**
 Selecting the move to suggest for the algorithm to attempt.
 Makes the move if the move is checked to be valid.
 */
void Maze::selectMove(){
    bool selectionMade = false;
    
    while(!selectionMade){
        int select = rand() % 4;            //Choose on the 4 directions
        rand();

        if (checkMove(select)){             //Ensure a valid move and make the move if so
                selectionMade = true;
                makeMove(select);
        }
    }
}

/**
 Checking the move to makes sure that it does not take us outside of the grid walls.
 @param int s - the key indicating the move desired.
 @return bool DO - false if the move is not valid, true otherwise.
 */
bool Maze::checkMove(int s){
    bool DO = false;            //If within boundaries
    
    if(s == 0){                 //Move Right
        if(cpj < n-1){
            DO = true;
        }
    }
    if(s == 1){                 //Move Up
        if(cpi > 0)
            DO = true;
    }
    if(s == 2){                 //Move Left
        if(cpj > 0)
            DO = true;
    }
    if(s == 3){                 //Move Down
        if(cpi < n-1)
            DO = true;
    }
    
    return DO;
}

/**
 Prints the current grid maze out to the terminal when called -- formmatted as a matrix.
 */
void Maze::toString(){
    std::string str = "";
    for(int i= 0; i < n; i++){
           for(int j = 0; j < n; j++){                          //print out 1/0 for each space
               str += std::to_string(maze[i][j]) + " ";         //Add space between each coordinate
           }
        str += "\n";                                            //Next line
       }
    cout << str << std::endl;
}

/*      --      Maze Solver     --       */

/**
The Efficient Solver Algorithm
 */
std::string Maze::solveE(){
  int curRow = 0;                   //Current Row
  int curCol = 0;                   //Current Col
  int prevRow = 0;
  int prevCol = 0;
  std::string path = "";
    setTestMaze();
  
  while(curRow != n - 1){
    int move = rand()%100;
    /**
     **check right
     ***allows for right to be picked 25% of the time
     **makes sure next move is in bounds
     **checks to see if there is a 1 to the right
     */
    if(move>=0 && move<25 && curCol < n - 1 && maze[curRow][curCol+1] == 1){
        /**
        **if it tries to go back to previous position
        **path starts over
        */
        if(prevCol==curCol+1 && prevRow==curRow){     //Resets if it goes backwards
          path = "";
          curRow = 0;
          curCol = 0;
          prevRow = 0;
          prevCol = 0;
            setTestMaze();
      }
      else{
        prevRow = curRow;
        prevCol = curCol;
        curCol = curCol + 1;
        path = path + "R ";
          testMaze[curRow][curCol] = 'x';
      }
    }
    /**
     **check up
     **allows for up to be picked 15% of the time
     **makes sure next move is in bounds
     **checks to see if there is a 1 above
     */
    if(move>=50 && move<65 && curRow >= 1 && maze[curRow-1][curCol] == 1){
        /**if it tries to go back to previous position
        **path starts over
         */
      if(prevRow==curRow-1 && prevCol==curCol){
          path = "";
          curRow = 0;
          curCol = 0;
          prevRow = 0;
          prevCol = 0;
          setTestMaze();
      }
      else{
        prevRow = curRow;
        prevCol = curCol;
        curRow = curRow -1;
        path = path + "U ";
          testMaze[curRow][curCol] = 'x';
      }
    }
    /**
     **check left
     **allows for left to be picked 25% of the time
     **makes sure next move is in bounds
     **checks to see if there is a 1 to the left
     */
    if(move>=25 && move<50 && curCol >= 1 && maze[curRow][curCol-1] == 1){
        /**
        **if it tries to go back to previous position
        **path starts over
        */

      if(prevCol==curCol-1 && prevRow==curRow){
          path = "";
        curRow = 0;
        curCol = 0;
        prevRow = 0;
        prevCol = 0;
          setTestMaze();
      }
      else{
        prevRow = curRow;
        prevCol = curCol;
        curCol = curCol - 1;
        path = path + "L ";
          testMaze[curRow][curCol] = 'x';
      }
    }
    /**
     **check down
     **allows for down to be picked 35% of the time
     **makes sure next move is in bounds
     **checks to see if there is a 1 below
     */
    if(move>=65 && move<100 && curRow < n - 1 && maze[curRow+1][curCol] == 1){
        /**
        **if it tries to go back to previous position
        **path starts over
        */
      if(prevRow==curRow+1 && prevCol==curCol){
        path = "";
        curRow = 0;
        curCol = 0;
        prevRow = 0;
        prevCol = 0;
          setTestMaze();
      }
      else{
        prevRow = curRow;
        prevCol = curCol;
        curRow = curRow + 1;
        path = path + "D ";
          testMaze[curRow][curCol] = 'x';
      }
    }

  }/**
    **while loop end
    */
    pathToString();
  return path;
}

void Maze::setTestMaze(){
    this-> testMaze = new char*[this->n];
    
    for(int i= 0; i < n; i++){              // Fill in the initial array with 0's
        testMaze[i] = new char[n];
        for(int j = 0; j < n; j++){
            testMaze[i][j] = maze[i][j];     // Each element is the same as the maze.
        }
    }
    testMaze[0][0] = 'x';
}

void Maze::pathToString(){
    std::string str = "";
    for(int i= 0; i < n; i++){
           for(int j = 0; j < n; j++){
               if(testMaze[i][j] == 'x')
                   str += "x ";         //Add space between each coordinate
               else
                   str+= std::to_string(testMaze[i][j]) + " ";
           }
        str += "\n";                                            //Next line
       }
    cout << str << std::endl;
}


#endif //Maze
