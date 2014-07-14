#include "typedef.h"
//Structure to hold the direction and value of pegs
struct PEG
{
  boolean data;
  struct PEG * _direction[6];
};

//Array of LEDs
node * led[15];

//current position pointer
node * current;

//Buttons
const int west = 6;
const int east = 7;
const int north_east = 8;
const int north_west = 9;
const int south_east = 10;
const int south_west = 11;
const int pick = 12;

//Shift Registers PiN cOnFig

//First Shift Register
const int data_serial = 0;
const int latch = 1;
const int clock = 2;

//Second Shift register
const int data_serial_2 = 3;
const int latch_2 = 4;
const int clock_2 = 5;


//Cursor position blink
boolean _blink = false;
long previousMillis = 0;
int blink_interval = 500;

//Global Iterator
int i,j;

//Flagging whether picking or placing!
boolean flag = false;

// temp variables
node * temp_1;
node * temp_2;
node * temp_3;

//Functions!!

//Intialise memory
void inti_memory()
{
  for( i = 0; i < 15; i++ )
  {
    led[i] = (PEG*) malloc ( sizeof(PEG) );
  }
}

//Start of game or Reset the board
void start_of_game()
{
  // top most LED in the triangle
  int start = 7;
  for( i = 0; i<15 ; i++ )
  {
    if( i == start )
    {
      led[i]->data = 0;
    }
    else
    {
      led[i]->data = 1;
    }
  }
}

//mapping the Leds and setting start
void mapping()
{
  //Node 0
  led[7]->_direction[0] = NULL;
  led[7]->_direction[1] = NULL;
  led[7]->_direction[2] = NULL;
  led[7]->_direction[3] = NULL;
  led[7]->_direction[4] = led[5];
  led[7]->_direction[5] = led[6];

  //Node 1
  led[6]->_direction[0] = NULL;
  led[6]->_direction[1] = led[5];
  led[6]->_direction[2] = led[7];
  led[6]->_direction[3] = NULL;
  led[6]->_direction[4] = led[3];
  led[6]->_direction[5] = led[4];

  //Node 2
  led[5]->_direction[0] = led[6];
  led[5]->_direction[1] = NULL;
  led[5]->_direction[2] = NULL;
  led[5]->_direction[3] = led[7];
  led[5]->_direction[4] = led[2];
  led[5]->_direction[5] = led[3];

  //Node 3
  led[4]->_direction[0] = NULL;
  led[4]->_direction[1] = led[3];
  led[4]->_direction[2] = led[6];
  led[4]->_direction[3] = NULL;
  led[4]->_direction[4] = led[0];
  led[4]->_direction[5] = led[1];

  //Node 4
  led[3]->_direction[0] = led[4];
  led[3]->_direction[1] = led[2];
  led[3]->_direction[2] = led[5];
  led[3]->_direction[3] = led[6];
  led[3]->_direction[4] = led[14];
  led[3]->_direction[5] = led[0];

  //Node 5
  led[2]->_direction[0] = led[3];
  led[2]->_direction[1] = NULL;
  led[2]->_direction[2] = NULL;
  led[2]->_direction[3] = led[5];
  led[2]->_direction[4] = led[13];
  led[2]->_direction[5] = led[14];

  //Node 6
  led[1]->_direction[0] = NULL;
  led[1]->_direction[1] = led[0];
  led[1]->_direction[2] = led[4];
  led[1]->_direction[3] = NULL;
  led[1]->_direction[4] = led[11];
  led[1]->_direction[5] = led[12];

  //Node 7
  led[0]->_direction[0] = led[1];
  led[0]->_direction[1] = led[14];
  led[0]->_direction[2] = led[3];
  led[0]->_direction[3] = led[4];
  led[0]->_direction[4] = led[10];
  led[0]->_direction[5] = led[11];

  //Node 8
  led[14]->_direction[0] = led[0];
  led[14]->_direction[1] = led[13];
  led[14]->_direction[2] = led[2];
  led[14]->_direction[3] = led[3];
  led[14]->_direction[4] = led[9];
  led[14]->_direction[5] = led[10];

  //Node 9
  led[13]->_direction[0] = led[8];
  led[13]->_direction[1] = NULL;
  led[13]->_direction[2] = NULL;
  led[13]->_direction[3] = led[2];
  led[13]->_direction[4] = led[8];
  led[13]->_direction[5] = led[9];

  //Node 10
  led[12]->_direction[0] = NULL;
  led[12]->_direction[1] = led[11];
  led[12]->_direction[2] = led[1];
  led[12]->_direction[3] = NULL;
  led[12]->_direction[4] = NULL;
  led[12]->_direction[5] = NULL;

  //Node 11
  led[11]->_direction[0] = led[12];
  led[11]->_direction[1] = led[10];
  led[11]->_direction[2] = led[0];
  led[11]->_direction[3] = led[1];
  led[11]->_direction[4] = NULL;
  led[11]->_direction[5] = NULL;

  //Node 12
  led[10]->_direction[0] = led[11];
  led[10]->_direction[1] = led[9];
  led[10]->_direction[2] = led[14];
  led[10]->_direction[3] = led[0];
  led[10]->_direction[4] = NULL;
  led[10]->_direction[5] = NULL;

  //Node 13
  led[9]->_direction[0] = led[10];
  led[9]->_direction[1] = led[8];
  led[9]->_direction[2] = led[13];
  led[9]->_direction[3] = led[14];
  led[9]->_direction[4] = NULL;
  led[9]->_direction[5] = NULL;

  //Node 14
  led[8]->_direction[0] = led[9];
  led[8]->_direction[1] = NULL;
  led[8]->_direction[2] = NULL;
  led[8]->_direction[3] = led[13];
  led[8]->_direction[4] = NULL;
  led[8]->_direction[5] = NULL;

  current = led[6];
}

//Printing the current state of the LEDs i.e lighting em' up :D
void print_state()
{
  //if ( current->data == 0 )
  //{
  //  flag = 0;
  //}
  // register 1
  digitalWrite(latch,LOW);
  for ( i = 0; i<8 ; i++ )
  {
    digitalWrite(clock,LOW);
    if ( led[i] == current )
    {
      digitalWrite(data_serial, ( _blink ? HIGH : LOW ) );
      _blink = !_blink;
    }
    else
    {
      digitalWrite(data_serial,led[i]->data);
    }
    digitalWrite(clock,HIGH);
  }
  digitalWrite(latch,HIGH);

  //Register 2
  digitalWrite(latch_2,LOW);
  for ( i = 8; i<15 ; i++ )
  {
    digitalWrite(clock_2,LOW);
    if ( led[i] == current )
    {
      digitalWrite(data_serial_2, ( _blink ? HIGH : LOW ) );
      _blink = !_blink;
    }
    else
    {
      digitalWrite(data_serial_2,led[i]->data);
    }
    digitalWrite(clock_2,HIGH);
  }
  digitalWrite(latch_2,HIGH);



  //  if ( flag == 0 )
  //  {
  //    delay(100);
  //  }
  //  else
  //  {
  //    delay(30);
  //  }


}

//GAME LOGIC

//Logic to handle the state and button press of the game
void button_press( int i )
{
  if ( flag == 0 )
  {
    traverse(i);
  }
  if ( flag == 1 )
  {
    if( check_move(i) == 1 )
    {
      make_move(i);
    }
  }
}

//make the move if valid!!
void make_move( int i )
{
  temp_1 = current->_direction[i];
  temp_2 = temp_1->_direction[i];
  current->data = 0;
  temp_1->data = 0;
  temp_2->data = 1;
  current = temp_2;
  flag = 0;
  if ( end_of_game() == 1 )
  {
    print_state();
    analogWrite(A0,255);
    delay(1000);
    analogWrite(A0,0);
    start_of_game();
  }
}

//checks for a valid move!
boolean check_move( int i )
{
  node * temp_current;
  temp_current = current;
  temp_2 = temp_current->_direction[i];
  if ( temp_2 != NULL )
  {
    if( temp_2->data != 0 )
    {
      temp_3 = temp_2->_direction[i];
      if ( temp_3 != NULL && temp_3->data != 1 )
      {
        return 1    ;
      }
    }
    else
    {
      return 0;
    }
  }
  return 0;
}


// traversing function i.e to move around 
void traverse( int i )
{
  temp_1 = current->_direction[i];
  if ( temp_1 != NULL )
  {
    current = temp_1;
  }
}
// end of game valid move
int check_move_eog(int i, int j)
{
  temp_1 = led[i]->_direction[j];
  temp_2 = temp_1->_direction[j];
  if ( led[i] != NULL )
  {
    if (temp_1 != NULL)
    {
      if ( temp_1->data == 1 )
      {
        if( temp_2 != NULL )
        {
          if ( temp_2->data == 0 )
          {
            return 1;
          }
        }
        else
        {
          return 0;
        }
      }
    }
  }    

}

//end of game
int end_of_game()
{
  int counter = 0;
  for ( i =0; i<15; i++)
  {
    if ( led[i]->data == 1 )
    {
      counter++;
    }
  }
  if ( counter > 7 )
  {
    return 0;
  }
  for ( i = 0; i<15; i++ )
  {
    if ( led[i]->data == 1 )
    {
      for ( j = 0 ; j<6; j++ )
      {
        if ( check_move_eog(i,j) == 1 )
        {
          return 0;
        }
      }
    }
  }
  return 1;
} 


void setup()
{
  //Shift register 1 output 
  pinMode(data_serial,OUTPUT);
  pinMode(latch,OUTPUT);
  pinMode(clock,OUTPUT);

  //Shift register 2 output 
  pinMode(data_serial_2,OUTPUT);
  pinMode(latch_2,OUTPUT);
  pinMode(clock_2,OUTPUT);

  //Buttons
  pinMode(west,INPUT_PULLUP);
  pinMode(east,INPUT_PULLUP);
  pinMode(north_east,INPUT_PULLUP);
  pinMode(north_west,INPUT_PULLUP);
  pinMode(south_east,INPUT_PULLUP);
  pinMode(south_west,INPUT_PULLUP);
  pinMode(pick,INPUT_PULLUP);

  //Intialising functions
  inti_memory();
  start_of_game();
  mapping();
  print_state();

  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);

}

void loop()
{

  //  print_state();
  int b_0 = digitalRead(west);
  int b_1 = digitalRead(east);
  int b_2 = digitalRead(north_east);
  int b_3 = digitalRead(north_west);
  int b_4 = digitalRead(south_east);
  int b_5 = digitalRead(south_west);
  boolean update_board = false;

  if ( b_0 == LOW )
  {
    button_press(0);
    update_board = true;
  } 
  else if ( b_1 == LOW )
  {
    button_press(1);
    update_board = true;
  }
  else if ( b_2 == LOW )
  {
    button_press(2);
    update_board = true;
  }
  else if ( b_3 == LOW )
  {
    button_press(3);
    update_board = true;
  }
  else if ( b_4 == LOW )
  {
    button_press(4);
    update_board = true;
  }
  else if ( b_5 == LOW )
  {
    button_press(5);
    update_board = true;
  }


  int b_6 = digitalRead(pick);

  if ( b_6 == LOW )
  {
    flag = !flag;
    //if ( flag >= 2 )
    //{
    //  flag = 0;
    //}

  }
  if(flag == 0)
  {
    blink_interval = 500;
  } 
  if (flag == 1) 
  {
    blink_interval = 150;
  }

  // todo -- change the interval based on board state
  if(millis() - previousMillis > blink_interval) {
    previousMillis = millis();
    update_board = true;
  }

  if(update_board) {
    print_state();
    delay(100);
  } 

  if (flag == 0)
  {
    analogWrite(A1,255);
    analogWrite(A2,0);
  }
  if ( flag == 1 )
  {
    analogWrite(A1,0);
    analogWrite(A2,255);
  }

}





