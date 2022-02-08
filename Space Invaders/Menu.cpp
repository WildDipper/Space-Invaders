//implementation of the menu class
#include "Menu.h"

Menu::Menu(string title, string* choiceList, int nbItem, int startLine, int startColumn){
	this->title_=title;
	this->choice_list_ = new string[nbItem];
	for(int i=0;i<nbItem;i++){
		this->choice_list_[i]=choiceList[i];
	}
	choiceList;
	this->nb_item_= nbItem;
	this->corner_ul_.X= startColumn;
	this->corner_ul_.Y= startLine;
	//initializing the positions
	init();
}

void Menu::init(){
	//initialization of the positions and the choice
	this->choice_=1;
	this->current_pos_.X = corner_ul_.X;
	this->current_pos_.Y = corner_ul_.Y+2;
	this->first_pos_= current_pos_;
	this->last_pos_= first_pos_;
	this->last_pos_.Y= first_pos_.Y+2*(nb_item_-1);
}

Menu::~Menu(){
	delete []this->choice_list_;

}

int Menu::displayMenu(){
	
	COORD nextPos=current_pos_;
	//draw the menu
	gotoXY(corner_ul_);
	cout<<title_<<endl;
	for(int i=0; i<nb_item_;i++){
		gotoXY(corner_ul_.X+4, first_pos_.Y+(2*i));
		cout<<choice_list_[i]<<endl;
	}
	//get arrow input
	int key;
	//move(_currentPos, _firstPos);
	move(current_pos_, current_pos_);
	do{	
		nextPos=current_pos_;
		key=_getch();
		if(key==224){
			key= _getch();
		}
		//move
		switch(key){
		case 80:	//down key
			if(current_pos_.Y==last_pos_.Y) //if we are already down
			{
				move(current_pos_, first_pos_);
				current_pos_ = first_pos_;
				choice_=1;
			}
			else
			{
				nextPos.Y+=2;
				move(current_pos_, nextPos);
				current_pos_.Y+=2;
				choice_++;
			}
			break;	
		case 72:	//up key
			if(current_pos_.Y==first_pos_.Y) //if we are already up
			{
				move(current_pos_,last_pos_);
				current_pos_=last_pos_;
				choice_=nb_item_;
			}
			else
			{
				nextPos.Y-=2;
				move(current_pos_, nextPos);
				current_pos_.Y-=2;
				choice_--;
			}
			break;
		default: ;
		}

	}while(key !=13);
	//return the choice
	
return choice_;
}


void Menu::move(COORD origin, COORD target){
	//erase
	gotoXY(origin);
	cout<<"   "<<endl;
	//draw
	gotoXY(target);
	cout<<"-->"<<endl;
}


int Menu::getMaxSize(){
	return 0;
}


void Menu::gotoXY(COORD pos){
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}


void Menu::gotoXY(int c, int l){
	COORD coord;
	coord.X=c;
	coord.Y=l;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
