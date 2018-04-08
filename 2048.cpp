# game

#include<iostream>
#include<cstdlib>
#include<fstream>
#include<string>
#include<vector>
#include<cmath>

int rowcoltoi(int x, int y, int rowlen);

void rotate_anti_clock(std::vector<int>& v);
void print_grid(const std::vector<int>& v);

bool random_two(std::vector<int>& v,bool pot_move);
bool game_over(const std::vector<int>& v);
bool merge_num(std::vector<int>& in,int bi,int ei);
bool move_grid(std::vector<int>& in,std::string operand);

int main()
{
     std::vector<int> g;

     std::string filename;

     std::cout << "enter initial configurational file name:" << std::endl;
     std::cin >> filename;

     std::ifstream infile;
     infile.open(filename.c_str());
     int i;
     if(!infile.is_open()){
          std::cout << "file not found, using default start configuration" << std::endl;
          for(i=0;i<15;i++)
          {
               g.push_back(0);
          }
          g.push_back(2);
     }
     else
     {
          int tmp;
          while(infile>>tmp)
          {
               g.push_back(tmp);
               i++;
          }
     }
     std::cout<<std::endl;
     print_grid(g);
     std::cout<<std::endl;
     std::cout<<std::endl;

     bool pot_move;
     std::string operand;
     while(!game_over(g))
     {
          std::cin>>operand;
          pot_move=move_grid(g,operand);
          if(pot_move)
          {
               random_two(g,pot_move);
               std::cout<<std::endl;
               std::cout<<std::endl;
               print_grid(g);
               std::cout<<std::endl;
               std::cout<<std::endl;
          }
     }
     std::cout<<"game over"<<std::endl;
     return 0;
}
int rowcoltoi(int x, int y, int rowlen){
     return x*rowlen+y;
}

void print_grid(const std::vector<int>& v){
     int side=std::sqrt(v.size());
     for(int i = 0; i < side; i++)
     {
         for(int j = 0; j < side; j++)
         {
             std::cout << v[rowcoltoi(i,j,side)] << "\t";
         }
         std::cout << std::endl;
     }
}
bool merge_num(std::vector<int>& in,int bi,int ei){
     int i;
     int j=0;

     std::vector<int> tmp;
     bool whether_merge=false;
     for(i=bi;i<ei;i++)
     {
          if(in[i]!=0)
          {
              tmp.push_back(in[i]);
              if(i!=(bi+j))
              {
                  whether_merge=true;
              }
              j++;
          }
     }

     int mergenum=0;
     j=0;
     for(i=0;i<tmp.size();i++)
     {
          if(i==tmp.size()-1)
          {
              in[bi+j]=tmp[i];
          }
          else if(tmp[i]==tmp[i+1])
          {
              in[bi+j]=2*tmp[i];
              i++;
              mergenum++;
              whether_merge=true;
          }
          else
          {
              in[bi+j]=tmp[i];
          }
          j++;
     }
     int exist_num=bi+tmp.size()-mergenum;
     for(i=exist_num;i<ei;i++)
     {
          in[i]=0;
     }
     return whether_merge;
}
void rotate_anti_clock(std::vector<int>& v){
     std::vector<int> tmp;
     for(int i=0;i<v.size();i++)
     {
          tmp.push_back(v[i]);
     }
     int side=sqrt(v.size());
     for(int i=0;i<side;i++)
     {
          for(int j=0;j<side;j++)
          {
               v[rowcoltoi(i,j,side)]=tmp[rowcoltoi(j,side-1-i,side)];
          }
     }
}
bool move_grid(std::vector<int>&in,std::string operand){
     int side=std::sqrt(in.size());
     bool whether_change=false;
     if(operand=="w")
     {
          rotate_anti_clock(in);
          for(int i=0;i<in.size();i=i+side)
          {
               if(merge_num(in,i,i+side))
               {
                    whether_change=true;
               }
          }
          rotate_anti_clock(in);
          rotate_anti_clock(in);
          rotate_anti_clock(in);
     }
     else if(operand=="a")
     {
          for(int i=0;i<in.size();i=i+side)
          {
               if(merge_num(in,i,i+side))
               {
                    whether_change=true;
               }
          }
     }
     else if(operand=="s")
     {
          rotate_anti_clock(in);
          rotate_anti_clock(in);
          rotate_anti_clock(in);
          for(int i=0;i<in.size();i=i+side)
          {
               if(merge_num(in,i,i+side))
               {
                    whether_change=true;
               }
          }
          rotate_anti_clock(in);
     }
     else if(operand=="d")
     {
          rotate_anti_clock(in);
          rotate_anti_clock(in);
          for(int i=0;i<in.size();i=i+side)
          {
               if(merge_num(in,i,i+side))
               {
                    whether_change=true;
               }
          }
          rotate_anti_clock(in);
          rotate_anti_clock(in);
     }
     return whether_change;
}
bool random_two(std::vector<int>& v,bool pot_move)
{
     int random_index;
     int j,i=0;
     std::vector<int> tmp;
     bool equal_index;
     while(i<v.size())
     {
         j=0;
         equal_index=false;
     	   random_index=rand()%v.size();
     	   while((j<tmp.size())&&(!equal_index))/*This is to ensure that no repetitive random index*/
         {
              if(tmp[j]==random_index)
              {
                   equal_index=true;
              }
              j++;
         }
         if(!equal_index)
         {
              tmp.push_back(random_index);
              if(v[random_index]==0)
              {
                   if(pot_move)
                   {
                        v[random_index]=2;
                        return true;
                   }
                   return false;
              }
              else
              {
                   i++;
              }
         }
	   }
     return false;
}
bool game_over(const std::vector<int>& v){
     int i,j,side;
     side=std::sqrt(v.size());
     for(i=0;i<v.size();i++)
     {
          if(v[i]==0)
          {
               return false;
          }
     }
     for(i=0;i<side-1;i++)
     {
          for(j=0;j<side-1;j++)/* This loop simutaneously checks the rows and the columns, except for the last column*/
          {
               if(v[rowcoltoi(i,j,side)]==v[rowcoltoi(i,j+1,side)])
               {
                    return false;
               }
               else if(v[rowcoltoi(j,i,side)]==v[rowcoltoi(j+1,i,side)])
               {
                    return false;
               }
          }
          if(v[rowcoltoi(i,side-1,side)]==v[rowcoltoi(i+1,side-1,side)])//check the last column
          {
               return false;
          }
     }
     return true;
}
