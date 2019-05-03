// FeatherPal.cpp : By reddit.com/user/Rafinhi/
//

#include <iostream> 
#include <string> 
#include <fstream>
#include <cstdlib>
#include <windows.h> //this lets us have wait time for cookies and server connections
#include <time.h>       /* time only needed to have good srand seed */
#include <process.h>



using namespace std;
//Variables which i dont reccomend changing manually if you dont know what you are doing, but they are global so it means they are important, right? :D
int maxY;// height of screen
int maxX;// width of screen
int  x_y[2] = { 0,0 }; //pair of coordinates
int TimeBetweenTap = 1500; //its the time our phone takes to react to taps on the same screen changing interface, when it does not perform connections to the server
int msgServerTime = 6000; //i guess 6 seconds is enough for connection to server if you dont live in Europe (since i do and im laggin sometimes "thonk")
int RD_wait_time = 15000;//15 seconds for rival domains map seems like ok time
const int n = 39;//39 is the length of whole adb tap command, later we add 1 so we also can fit the null
int looperinio = 1;

//range of the Rival domains difficulty button position IN % /100
float rd_selectDifficultyXmin = 0.28;
float rd_selectDifficultyXmax = 0.79;
float rd_selectDifficultyYmin = 0.49;
float rd_selectDifficultyYmax = 0.52;

//range of the Rival domains difficulty confirm button position IN 
float rd_confirmDifficultyXmin = 0.30;
float rd_confirmDifficultyXmax = 0.72;
float rd_confirmDifficultyYmin = 0.72;
float rd_confirmDifficultyYmax = 0.76;

//range of the space on screen where ill click like mad man to skip some of the animations (gives like 2 or 3 seconds improvement in every loop so why not, also if you quickly double tap the same place you might make unit skip turn but you need to do it very quickly so instead of doubling this for other side of screen lets solve it inside of the function which needs it
float random_click_Xmin = 0.01;
float random_click_Xmax = 0.05;
float random_click_Ymin = 0.62;
float random_click_Ymax = 0.66;

//range of the after Rival domains "OK" button position 
float rd_OKXmin = 0.32;
float rd_OKXmax = 0.78;
float rd_OKYmin = 0.85;
float rd_OKYmax = 0.89;

//range of the autobattle button position 
float AB_Xmin = 0.74;
float AB_Xmax = 0.79;
float AB_Ymin = 0.94;
float AB_Ymax = 0.96;

//range of the confirm autobattle button position 
float AB_OK_Xmin = 0.29;
float AB_OK_Xmax = 0.70;
float AB_OK_Ymin = 0.47;
float AB_OK_Ymax = 0.50;


void set_random_point(float min_x,float max_x, float min_y, float max_y) {//note to self, why did i pick C++ and now i have to use pointers because i cannot return array natively ;///note 2: im stupid, lets just not return anything and just set global array with the coordinates
	//unsigned int seed;//its allocated every time function runs so it will rarely be the same but apparently not possibru in c++
	int omega_yato,yato_min,yato_max;	//we need some backup variables to deal with multiplying floats and ints while also dealing with rand
	//static int  x_y[2]; //its global now

	srand(time(NULL));//we use time to get better randomization,i didnt dont want to add another library, but just using unsigned int which we dont set value to so it has value of some random memory space  made my visual studio go cowabunga
	yato_min = maxX * min_x;//minimum pixel position of x coordinate
	yato_max = maxX * max_x;//maximum pixel position of x coordinate
	omega_yato = rand(); //some random number
	x_y[0]= omega_yato % (yato_max - yato_min) + yato_min; //first number in our tab gets the chosen x coordinate
	yato_min = maxY * min_y; //minimum pixel position of y coordinate
	yato_max = maxY * max_y; //maximum pixel position of y coordinate
	x_y[1] = omega_yato % (yato_max - yato_min) + yato_min; //second number in our tab gets the chosen y coordinate
	
}

void adb_click(int x, int y) {
	string click;
	//we have to turn integers into strings because otherwise you couldn't concatenate them to the rest :I
	click = string(".\\adb\\adb.exe shell input tap ") + to_string(x) + ' ' + to_string(y);
	//now we will do stuff nobody should do, if you do this you might break the universe in half or interfere with doctor's strange plan
	//int n = click.length();//it had to be constant so i couldnt declare it here, it might change one day but i guess then ill just have to manually count the characters (also if the length changes it means that screen resolution went above 9999 pixels or the adb command changed so anyway everything would break;/
	char char_array[n + 1]; //we declare array of characters
	strcpy_s(char_array, click.c_str()); //we copy content of click to the array
	system(char_array); //we send the array to system console (we couldnt send it as whole string because reasons)
}

void adb_screensize() {
	string temp_string;
	
	system(".\\adb\\adb.exe shell wm size>screenSize.txt"); //since im a monkey and google gives close to 0 documentation
	//about using adb as library in c++ (or im giga bad in searching google)(and also i dont want to include and compile whole adb here just so i can use two functions
	//i just use windows console + precompiled adb to save screen size into file

	//here we read file and extract info about screensize;/
	ifstream Reader;  //Create input from file
	Reader.open("screenSize.txt"); //open the file we just made
	if (Reader.is_open()) {
		getline(Reader, temp_string); // we save the line into temporary string
					}
		Reader.close();        //Close file
				
		maxY = stoi(temp_string.substr(temp_string.size() - 5, temp_string.size()-2));//this is the position of screen height in the file, we change string into int
		maxX = stoi(temp_string.substr(temp_string.size() - 11, temp_string.size() - 8));//position of width
		//and woah, we suddenly have magic knowledge of physical screen size, also note to self: if the screen height is less than 1000 it will break, but i dont think there are any phones who work with feh and also have screen which is like 740x480  :3
		}

void print_feh_the_owl() {
	string LOGO;
	
	ifstream Reader;  //Create input from file
	Reader.open("logo.txt"); //open the logo file
	if (Reader.is_open()) {
		while (!Reader.eof()) {				   

			getline(Reader, LOGO); // Saves the line in STRING.
			cout << LOGO<<endl; // Prints our STRING.
			
		}
		cout << endl << endl;
		Reader.close();        //Close file
	}
	else cout << "File does not exist"<<endl<<endl;
}

void click_like_mad_man() {//this clicks 4 times on the sides of screen (4 times the TimeBetweenTaps, usually the default 6 seconds seem like good enough time)
	for (int i = 0; i < 2; i++) {
		Sleep(TimeBetweenTap);//we sleep a while
		set_random_point(random_click_Xmin, random_click_Xmax, random_click_Ymin, random_click_Ymax);// we set point on the side of screen to tap
		adb_click(x_y[0], x_y[1]);//we click on the random spot
		Sleep(TimeBetweenTap);//we sleep a while
		adb_click((maxX - x_y[0]), x_y[1]);//we click on the random spot but on the other side of screen
	}
}


void __cdecl ThreadOfDestiny(void* Args)
{
	while (looperinio != 0) cin >> looperinio;
	cout << "Ending after this loop!"<<endl;
	_endthread();
}

void rival_domains() {
	int grey_waves_count = 0;
	looperinio = 1;
	_beginthread(ThreadOfDestiny, 0, NULL);  // create the thread which we will use to let people go out of loop
	//some kind of looperinio?
	while (looperinio) {
		cout << "Now battling Rival Domains!" << " - Send 0 to stop!" << endl << endl << "Times fought: " << grey_waves_count << endl << endl<<endl;
		
		//select_difficulty
		//int* click_pointer;//pointer to the array which has coordinates for next click;//not needed anymore
		cout << "Choosing difficulty!" << endl << endl;
		set_random_point(rd_selectDifficultyXmin, rd_selectDifficultyXmax, rd_selectDifficultyYmin, rd_selectDifficultyYmax);//we set random poin on the difficulty button to click on
		adb_click(x_y[0], x_y[1]);//we click on difficulty button
		Sleep(TimeBetweenTap);//we sleep

		set_random_point(rd_confirmDifficultyXmin, rd_confirmDifficultyXmax, rd_confirmDifficultyYmin, rd_confirmDifficultyYmax);// we set random point on the confirm button
		adb_click(x_y[0], x_y[1]);//we click on confirm button
		cout << "Clicking to skip starting screen!" << endl << endl;
		//click_like_mad_man
		click_like_mad_man();
		cout << "Selecting autobattle!" << endl << endl;
		//select_autobattle
		set_random_point(AB_Xmin, AB_Xmax, AB_Ymin, AB_Ymax);//we set random poin on the autobattle button
		adb_click(x_y[0], x_y[1]);//we click on autobattle button
		Sleep(TimeBetweenTap);//we sleep
		set_random_point(AB_OK_Xmin, AB_OK_Xmax, AB_OK_Ymin, AB_OK_Ymax);// we set random point on the confirm button
		adb_click(x_y[0], x_y[1]);//we click on confirm button
		cout << "Sleeping till autobattle finishes! " << endl << endl;
		//wait_in_here
		Sleep(RD_wait_time);//we sleep
		cout << "Closing end screen! " << endl << endl;
		//closeRD
		set_random_point(rd_OKXmin, rd_OKXmax, rd_OKYmin, rd_OKYmax);//we set random point on the OK button
		adb_click(x_y[0], x_y[1]);//we click on the end screen
		Sleep(TimeBetweenTap*2);//we sleep so game can go to the ok button
		adb_click(x_y[0], x_y[1]);//we click on the ok button 
		Sleep(TimeBetweenTap);//we sleep so game can go back to the map choice
		grey_waves_count++;
		system("cls");
	}
	cout << "Have a nice day! " << endl << endl;
}

void menu() {
	int you_are_the_oceans_grey_waves;
	
	cout << "What do you want to do? Choose number and press enter" << endl << endl;
	cout << "1 -> Rival Domains farming (Lunatic mode)" << endl << endl;
	cout << "2 -> Check Screen Size" << endl << endl;
	cout << "0 -> Escape" << endl << endl;
	
	cin >> you_are_the_oceans_grey_waves;
	system("cls");
	switch (you_are_the_oceans_grey_waves)
	{
	case 0:	break;

	case 1:
		adb_screensize();
		rival_domains();
		break;
	case 2:
		adb_screensize();
		cout << "Your screen is " << maxX << " pixels wide, and " << maxY <<" pixels high"<< endl<<endl;
		menu();
		break;

	default:
		cout << "There is no such option, choose wisely"<<endl;
			menu();
		break;
	}

}



int main()
{
	//Print Feh the Owl and Logo
	print_feh_the_owl();
	//spawn Menu
	menu();
	
    cout << "Closing\n";
	return 0;
}

