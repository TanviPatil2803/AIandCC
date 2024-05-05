#include<bits/stdc++.h>
using namespace std;


struct cell{
    int parent_i,parent_j;
    double g,h,f;
};

bool isDestination(int row, int col,pair<int,int>&dest){
    if(row==dest.first && col==dest.second)return true;
    return false;
}


bool isValid(int row, int col, int n, int m){
    if(row<0 || row>=n || col<0 || col>=m)return false;
    return true;
}

bool isUnblocked(int row, int col, vector<vector<int>>&grid){
    if(grid[row][col]==0)return false;
    return true;
}

double calculateHvalue(int row, int col, pair<int,int>&dest){
    return double(sqrt(((row-dest.first)*(row-dest.first)+((col-dest.second)*(col-dest.second)))));
}

void trace_path(pair<int,int>&dest, vector<vector<cell>>&celldetail){
    int row=dest.first;
    int col=dest.second;
    cout<<"Path is as follows"<<endl;
    stack<pair<int,int>>st;
    while(!(celldetail[row][col].parent_i==row && celldetail[row][col].parent_j==col)){
        st.push({row,col});
        int prow=celldetail[row][col].parent_i;
        int pcol=celldetail[row][col].parent_j;
        row=prow;
        col=pcol;
    }
    st.push({row,col});
   
    while(!st.empty()){
        int i=st.top().first;
        int j=st.top().second;
        st.pop();
        cout<<"("<<i<<","<<j<<")->  ";
    }
}

void astarsearch(vector<vector<int>>&grid,pair<int,int>&src, pair<int,int>&dest, int n, int m){
    if(! isValid(src.first,src.second,n,m)){
        cout<<"Source is invalid"<<endl;
        return;
    }
    if(! isValid(dest.first,dest.second,n,m)){
        cout<<"Destination is invalid"<<endl;
        return;
    }
    if(!isUnblocked(src.first,src.second,grid) && !isUnblocked(dest.first, dest.second,grid)){
        cout<<"source or destination is invalid"<<endl;
        return;
    }
    if(isDestination(src.first,src.second,dest)){
        cout<<"Source is destination"<<endl;
        return;
    }
    
    vector<vector<bool>>closed_list(n,vector<bool>(m,false));//visited node
    vector<vector<cell>>celldetail(n,vector<cell>(m));
    
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
          //   cout<<"HEyy"<<endl;
            celldetail[i][j].g=FLT_MAX;
            celldetail[i][j].h=FLT_MAX;
            celldetail[i][j].f=FLT_MAX;
            celldetail[i][j].parent_i=-1;
            celldetail[i][j].parent_j=-1;
        }
    }
    int i,j;
     i=src.first;
     j=src.second;
      celldetail[i][j].g=0.0;
      celldetail[i][j].h=0.0;
      celldetail[i][j].f=0.0;
      celldetail[i][j].parent_i=i;
       celldetail[i][j].parent_j=j;
       

       bool destfound=false;
       set<pair<double,pair<int,int>>>open_list;
       open_list.insert({celldetail[i][j].f,{i,j}});
       while(!open_list.empty()){
           pair<double,pair<int,int>>pr= *open_list.begin();
           int row=pr.second.first;
           int col=pr.second.second;
           open_list.erase(open_list.begin());
           closed_list[row][col]=true;
          // cout<<row<<"  "<<col<<endl;
            // 8  Sucessors
           for(int k=-1;k<2;k++){
               for(int l=-1;l<2;l++){
                   double newg,newh,newf;
                   if(k==0 && l==0)continue;
                   int rowx=row+k;
                   int colx=col+l;
                   if(isValid(rowx,colx,n,m)){
                      if(isDestination(rowx,colx,dest)){
                          celldetail[rowx][colx].parent_i=row;
                          celldetail[rowx][colx].parent_j=col;
                          cout<<"Destination Found"<<endl;
                          destfound=true;
                          trace_path(dest,celldetail);
                          return;
                         
                      }
                      else if(closed_list[rowx][colx]==false && isUnblocked(rowx,colx,grid)){
                          if((k==-1 && l==-1) || (k==1 && l==1)|| (k==1 && l==-1) || (k==-1 && l==1)) newg=celldetail[row][col].g+1.414;
                          else newg=celldetail[row][col].g+1;
                          newh=calculateHvalue(rowx,colx,dest);
                          newf=newg+newh;
                         
                          if(celldetail[rowx][colx].f>newf){
                              open_list.insert({newf,{rowx,colx}});
                              celldetail[rowx][colx].g=newg;
                              celldetail[rowx][colx].h=newh;
                              celldetail[rowx][colx].f=newf;
                              celldetail[rowx][colx].parent_i=row;
                              celldetail[rowx][colx].parent_j=col;
                             
                          }
                      }        
                   }
               }
           }
         
           
           
           
       }
       
       if(destfound==false){
           cout<<"destination not found"<<endl;
           return;
       }
     
     return;
   
   
   
}
int main(){
   
    int n=9;
    int m=10;
    vector<vector<int>>grid= { 
{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
{ 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
{ 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
{ 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 } };

pair<int,int>src={8,0};
pair<int,int>dest={0,0};
cout<<"A* search started"<<endl;
astarsearch(grid,src,dest,n,m);

}
