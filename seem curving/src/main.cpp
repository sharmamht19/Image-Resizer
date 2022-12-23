#include <iostream>
#include <fstream>
#include<math.h>

using namespace std;

void Vert_DP(double **Energy ,int H,int W){

//Verticl DP--------------------------------------------------------------------------------------------------------------------------------
    for(int i = 1; i < H; ++i) {
        for(int j = 0; j < W; ++j) { 
             if(j==0){
                if(Energy[i-1][0]<Energy[i-1][1])
                    Energy[i][0]=Energy[i][0]+Energy[i-1][0];
                else
                    Energy[i][0]=Energy[i][0]+Energy[i-1][1];
             }
             else if(j==W-1)
             {
                if(Energy[i-1][W-1]<Energy[i-1][W-2])
                    Energy[i][W-1]=Energy[i][W-1]+Energy[i-1][W-1];
                else
                    Energy[i][W-1]=Energy[i][W-1]+Energy[i-1][W-2];

             }
             else
             {
                
               if(Energy[i-1][j-1]<Energy[i-1][j] && Energy[i-1][j-1]<Energy[i-1][j+1] ){
                Energy[i][j]=Energy[i][j]+Energy[i-1][j-1];
               }
                else if(Energy[i-1][j]<Energy[i-1][j-1] && Energy[i-1][j]<Energy[i-1][j+1]){
                     Energy[i][j]=Energy[i][j]+Energy[i-1][j];
                }
                 else{
                     Energy[i][j]=Energy[i][j]+Energy[i-1][j+1];
                 }
                 
             }
            }
        }
    

    
}
void Horizon_DP(double **Energy ,int H,int W){

//Horizontal   DP--------------------------------------------------------------------------------------------------------------------------------
    for(int j = 1; j < W; ++j) {
        for(int i = 0; i < H; ++i) { 
             if(i==0){
                if(Energy[0][j-1]<Energy[1][j-1])
                    Energy[0][j]=Energy[0][j]+Energy[0][j-1];
                else
                    Energy[0][j]=Energy[0][j]+Energy[1][j-1];
             }
             else if(i==H-1)
             {
                if(Energy[H-1][j-1]<Energy[H-2][j-1])
                    Energy[H-1][j]=Energy[H-1][j]+Energy[H-1][j-1];
                else
                    Energy[H-1][j]=Energy[H-1][j]+Energy[H-2][j-1];

             }
             else
             {
                
               if(Energy[i-1][j-1]<Energy[i][j-1] && Energy[i-1][j-1]<Energy[i+1][j-1] ){
                Energy[i][j]=Energy[i][j]+Energy[i-1][j-1];
               }
                else if(Energy[i][j-1]<Energy[i-1][j-1] && Energy[i][j-1]<Energy[i+1][j-1]){
                     Energy[i][j]=Energy[i][j]+Energy[i][j-1];
                }
                 else{
                     Energy[i][j]=Energy[i][j]+Energy[i+1][j-1];
                 }
                 
             }
            }
        }
    
}
void solve(int ***rgb, int H, int W, int C, int H_, int W_, int C_) {
    // We've provided you the driver.py and main.cpp for your convinience
    // Please go through them and understand the file handling and input/output format
    // Feel free to experiment on your own

    // can access the array using rgb[i][j][k] like a regular 3D array

    // Write your code here
int R_ , G_ , B_ , Del_X,Del_Y ,Pix_En;
double **Energy;

Energy = new double *[H];
for(int i=0;i<H;i++){
    Energy[i] = new double [W];
}



while(H>H_){

 /*       
     cout<<"Your RGB matrix is like : "<<endl;
    
    for(int i = 0; i < H; ++i) {
        for(int j = 0; j < W; ++j) {
        cout<<"(";
            for(int k = 0; k < C; ++k) {
                cout<< rgb[i][j][k] << " ";
            }
            cout<<")  ";
        }
        cout<<endl;
}
*/
//cout<<endl;

for(int i = 0; i < H; ++i) {
        for(int j = 0; j < W; ++j) {    
            R_=rgb[i][(j+1+W)%W][0]-rgb[i][(j-1+W)%W][0];
            G_=rgb[i][(j+1+W)%W][1]-rgb[i][(j-1+W)%W][1];
            B_=rgb[i][(j+1+W)%W][2]-rgb[i][(j-1+W)%W][2];
            Del_X=R_*R_+G_*G_+B_*B_;  

            R_=rgb[(i+1+H)%H][j][0]-rgb[(i-1+H)%H][j][0];
            G_=rgb[(i+1+H)%H][j][1]-rgb[(i-1+H)%H][j][1];
            B_=rgb[(i+1+H)%H][j][2]-rgb[(i-1+H)%H][j][2];
            Del_Y=R_*R_+G_*G_+B_*B_;  

            Pix_En=Del_X+Del_Y;
            Energy[i][j]=sqrt(Pix_En);
        }
}
/*
 cout<<"Energy matrix is : "<<endl;
for(int i = 0; i < H; ++i) {
        for(int j = 0; j < W; ++j) { 
            cout<<Energy[i][j]<<"   ";
            }
            cout<<endl;
        }
        cout<<endl;
        */
Horizon_DP(Energy,H,W);
   
/*
 cout<<"Energy matrix  after Horizontal DP is : "<<endl;
for(int i = 0; i < H; ++i) {
        for(int j = 0; j < W; ++j) { 
            cout<<Energy[i][j]<<"   ";
            }
            cout<<endl;
        }
        cout<<endl; 
*/
//Shifting of pixel---------------------------------------For Horizontal seaming----------------------------------------------------------------------------    
    int Pos=0;
    double Min_val=Energy[0][W-1];
    for(int j=0;j<H;j++)
    {
        if(Energy[j][W-1]<Min_val){
            Pos=j;
            Min_val=Energy[j][W-1];

        }
    }
    int Temp[W];
    Temp[W-1]=Pos;
    int i=W-1;
    for(;i>0;i--){
         if(Pos==0){
                if(Energy[0][i-1]<Energy[1][i-1])
                    Pos=0;
                else
                    Pos=1;
             }
             else if(Pos==H-1)
             {
                if(Energy[H-1][i-1]<Energy[H-2][i-1])
                    Pos=H-1;
                else
                    Pos=H-2;
             }
             else
             { 
               if(Energy[Pos-1][i-1]<Energy[Pos][i-1] && Energy[Pos-1][i-1]<Energy[Pos+1][i-1] )
                 Pos=Pos-1;
                else if(Energy[Pos][i-1]<Energy[Pos-1][i-1] && Energy[Pos][i-1]<Energy[Pos+1][i-1])
                      Pos=Pos;
                 else
                     Pos=Pos+1;
            }
        Temp[i-1]=Pos;
       
    }
  
  // cout<<endl;

 for(int i = 0; i < W; ++i) {
        for(int j=Temp[i]; j <H-1; ++j) { 
              rgb[j][i]=rgb[j+1][i];
            }
        }

/*
 cout<<"Energy matrix  after  seaming is : "<<endl;
for(int i = 0; i < H-1; ++i) {
        for(int j = 0; j < W; ++j) {
        cout<<"(";
            for(int k = 0; k < C; ++k) {
                cout<< rgb[i][j][k] << " ";
            }
            cout<<")  ";
        }
        cout<<endl;
}
cout<<endl;
*/

    H--;
}
while(W>=W_){

 /*       
     cout<<"Your RGB matrix is like : "<<endl;
    
    for(int i = 0; i < H; ++i) {
        for(int j = 0; j < W; ++j) {
        cout<<"(";
            for(int k = 0; k < C; ++k) {
                cout<< rgb[i][j][k] << " ";
            }
            cout<<")  ";
        }
        cout<<endl;
}
*/
//cout<<endl;

for(int i = 0; i < H; ++i) {
        for(int j = 0; j < W; ++j) {    
            R_=rgb[i][(j+1+W)%W][0]-rgb[i][(j-1+W)%W][0];
            G_=rgb[i][(j+1+W)%W][1]-rgb[i][(j-1+W)%W][1];
            B_=rgb[i][(j+1+W)%W][2]-rgb[i][(j-1+W)%W][2];
            Del_X=R_*R_+G_*G_+B_*B_;  

            R_=rgb[(i+1+H)%H][j][0]-rgb[(i-1+H)%H][j][0];
            G_=rgb[(i+1+H)%H][j][1]-rgb[(i-1+H)%H][j][1];
            B_=rgb[(i+1+H)%H][j][2]-rgb[(i-1+H)%H][j][2];
            Del_Y=R_*R_+G_*G_+B_*B_;  

            Pix_En=Del_X+Del_Y;
            Energy[i][j]=sqrt(Pix_En);
        }
}
/*
 cout<<"Energy matrix is : "<<endl;
for(int i = 0; i < H; ++i) {
        for(int j = 0; j < W; ++j) { 
            cout<<Energy[i][j]<<"   ";
            }
            cout<<endl;
        }
        cout<<endl;
        */


Vert_DP(Energy,H,W);
        
 //Shifting of pixel---------------------------------------For Vertical seaming----------------------------------------------------------------------------    
    int Pos=0;
    double Min_val=Energy[H-1][0];
    for(int j=0;j<W;j++)
    {
        if(Energy[H-1][j]<Min_val){
            Pos=j;
            Min_val=Energy[H-1][j];

        }
    }
    int Temp[H];
    Temp[H-1]=Pos;
    int i=H-1;
    for(;i>0;i--){
         if(Pos==0){
                if(Energy[i-1][0]<Energy[i-1][1])
                    Pos=0;
                else
                    Pos=1;
             }
             else if(Pos==W-1)
             {
                if(Energy[i-1][W-1]<Energy[i-1][W-2])
                    Pos=W-1;
                else
                    Pos=W-2;
             }
             else
             { 
               if(Energy[i-1][Pos-1]<Energy[i-1][Pos] && Energy[i-1][Pos-1]<Energy[i-1][Pos+1] )
                 Pos=Pos-1;
                else if(Energy[i-1][Pos]<Energy[i-1][Pos-1] && Energy[i-1][Pos]<Energy[i-1][Pos+1])
                      Pos=Pos;
                 else
                     Pos=Pos+1;
            }
        Temp[i-1]=Pos;
       
    }
  
   //cout<<endl;

 for(int i = 0; i < H; ++i) {
        for(int j=Temp[i]; j <W-1; ++j) { 
              rgb[i][j]=rgb[i][j+1];
            }
        }

/*
 cout<<"Energy matrix  after  seaming is : "<<endl;
for(int i = 0; i < H; ++i) {
        for(int j = 0; j < W-1; ++j) {
        cout<<"(";
            for(int k = 0; k < C; ++k) {
                cout<< rgb[i][j][k] << " ";
            }
            cout<<")  ";
        }
        cout<<endl;
}
cout<<endl;
  */
  W--;
}



}

int main() {
    
    string ip_dir = "./data/input/";
    string ip_file = "rgb_in.txt";
    ifstream fin(ip_dir + ip_file);

    int H, W, C;
    fin >> H >> W >> C;
    
    int ***rgb;
    rgb = new int **[H];
    for(int i = 0; i < H; ++i) {
        rgb[i] = new int *[W];
        for(int j = 0; j < W; ++j) {
            rgb[i][j] = new int[C];
            for(int k = 0; k < C; ++k)
                fin >> rgb[i][j][k];
        }
    }
    fin.close();

    int H_, W_, C_;
    cout << "Enter new value for H (must be less than " << H << "): ";
    cin >> H_;
    cout << "Enter new value for W (must be less than " << W << "): ";
    cin >> W_;
    cout << '\n';
    C_ = C;

    solve(rgb, H, W, C, H_, W_, C_);

    string op_dir = "./data/output/";
    string op_file = "rgb_out.txt";
    ofstream fout(op_dir + op_file);
    
    fout << H_ << " " << W_ << " " << C_ << endl;
    for(int i = 0; i < H_; ++i) {
        for(int j = 0; j < W_; ++j) {
            for(int k = 0; k < C_; ++k) {
                fout << rgb[i][j][k] << " ";
            }
        }
        fout << '\n';
    }
    fout.close();
    //-------------------------------------------------------------my code--------------------------------------------------------------
   
    return 0;
}