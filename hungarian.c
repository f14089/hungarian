/*Brief Description: the hungarian method is implemented by graph theory 
and Depth First Search Algorithm.*/
/*Last Modified: 2017/05/08*/
/*Author: Jian*/
/*This is simple implementation for hungarian algorithm.*/
/*Hungarian Method is used to solve assignment problem, and we can get a minimum cost solution.*/
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define rows 10
#define cols 10
#define INF 0x7ffffff
int matrix[rows][cols] = 
{
{-6 ,-6, -6, -6 ,-6,-6,-6,-6,-6,-6},
{-6 ,-6, -6, -6 ,-6,-6,-6,-6,-6,-6},
{-15, -6, -13, -6,-6,-6,-6,-6,-6,-6}, 
{-6 ,-6, -6, -6 ,-6,-6,-6,-6,-6,-6},
{-6 ,-6, -6, -6 ,-6,-6,-6,-6,-6,-6},
{-21 ,-6, -6 ,-6 ,-6,-6,-6,-6,-6,-6},
{-6 ,-6, -10, -6 ,-6,-6,-6,-6,-6,-6},
{-6 ,-6, -6, -6 ,-6,-6,-6,-6,-6,-6},
{-6 ,-6, -6, -6 ,-6,-6,-6,-6,-6,-6},
{-19 ,-6, -7, -6 ,-6,-6,-6,-6,-6,-6},
};
int map[rows+1][cols+1];
int vis[2*rows+1];
int match[rows+1] = {0};/*node matching recording array.*/

int newpos[2*rows+1] = {0};/*recording the sequence of node by DFS algorithm.*/

int now = 0; /*visiting node index.*/

/*when the DFS algorithm is excuting, recording the parent node sequence.*/
int parent[2*rows] = {0};

int test[2*rows][2*cols];

/* vertex coloring array, if the entry was colored (the value  is 1), meaning the node 
cover the corresponding edges.*/
int set[2*rows] = {0}; 

void DFS(int x){
	int i,j;
	newpos[now++] = x;
	vis[x] = 1;
	for(i = 1; i < 2*rows + 1; i++){
		if(vis[i]==0 && test[x-1][i-1] == 1) {
			printf("x:%d i:%d\n",x,i);
			parent[i-1] = x;
			DFS(i);	
		}
	}
}

int min_vertex_cover(){
	int s[2*rows] = {0};
	int ans2=0;
	int i ;
	int t;
	int mark_row[rows] = {0};
	int mark_col[cols] = {0};
	memset(set,0,sizeof(set));
	for(i=rows+1;i<2*rows+1;i++){
		memset(vis,0,sizeof(vis));
		if(max_match(i)) ans2++;
	}
	for(i=rows;i<2*rows;i++){
		if(set[i] == 0){
			mark_row[i-rows] = 1;
			for(t=1;t<cols+1;t++){
				if(map[i-rows+1][t] == 1){
					mark_col[t-1] = 1;
					mark_row[match[t]-rows-1] = 1;
				}
			}
		}
	}
	memset(set,0,sizeof(set));
	for(i=0;i<rows;i++){
		if(mark_row[i] != 1){set[i] = 1;}
		if(mark_col[i] == 1){set[i+cols] = 1;}
	}
	for(i=0;i<2*rows;i++){
		printf("%d ",set[i]);
	}
	printf("\n");

	return ans2;
}
int max_match(int p){
	int i,j;
	for(i=1;i<cols+1;i++){
		if(!vis[i] && map[p-cols][i]){
			vis[i] = 1;
			if(!match[i] || max_match(match[i])){
				set[p-1] = 1;
				match[i] = p;
				return 1; 
			}
		}
	}
	return 0;
}
int main(){
	int row_min[rows] = {0};
	int col_min[cols] = {0};
	int i,j;
	int ans=0;
	int min;
	int MVC;
	int node_num = 0;
	/*Initialize the row_minimum and col_minimum because of hungarian method which 
	 find the minimum weighted bipartite graph.*/
	for(i=0;i<rows;i++){row_min[i] = INF;}
	for(i=0;i<cols;i++){col_min[i] = INF;}
	/*step 1: substract the minimum value for each rows.
	  step 2: substract the minimum value for each columns.
	  we do this calculation because we want to decrease the hungarian iteration time.
	  */
	for(i = 0; i < rows; i++){
		for(j = 0;j < cols;j++){
			if(row_min[i] > matrix[i][j]){row_min[i] = matrix[i][j];}
		}
		for(j=0;j<cols;j++){
			matrix[i][j] -= row_min[i];
		}
	}
	for(i=0;i<cols;i++){
		for(j=0;j<rows;j++){
			if(col_min[i] > matrix[j][i]){col_min[i] = matrix[j][i];}
		}
		for(j=0;j<rows;j++){
			matrix[j][i] -= col_min[i];
		}
	}
	printf("matrix111\n");
	for(i=0;i<rows;i++){
		for(j=0;j<cols;j++){
			printf("%d ",matrix[i][j]);
		}
		printf("\n");
	}
	//sleep(3);
	/*********************step 1 and step 2 finish.**************************/

	/*Iteration start*/
	/*step 3: because of step 1 and step 2, we got the equivalent weight for 
	this bipartite graph.
	For the matrix which is calulated by step 1 and step 2, we created a mapping matrix,
	if the matrix entries is zero, the entry of mapping matrix will be set to 1. 
	*/
	iteration:
	printf("matrix111\n");
	for(i=0;i<rows;i++){
		for(j=0;j<cols;j++){
			printf("%d ",matrix[i][j]);
		}
		printf("\n");
	}
	now = 0;
	memset(newpos,0,sizeof(newpos));
	memset(parent,0,sizeof(parent));
	memset(match,0,sizeof(match));
	memset(vis,0,sizeof(vis));
	memset(set,0,sizeof(set));
	for(i=0;i<rows;i++){
		for(j=0;j<cols;j++){
			if(matrix[i][j] == 0) {
				map[i+1][j+1] = 1;
			}
			else {
				map[i+1][j+1] = 0;
			}
		}
	}
	/*step 4: bipartite graph is trasformed to matrix*/
	for(i=0;i<2*rows;i++){
		for(j=0;j<2*cols;j++){
			if(i < rows && j < cols) test[i][j] = 0;
			else if (i < rows && j >= cols) test[i][j] = map[i+1][j - (cols - 1)];
			else if (i >= rows && j >= cols) test[i][j] = 0;
			else if (i >= rows && j < cols) test[i][j] = map[j+1][i-(cols - 1)];
		}
	}
	/**************************************/
	
	i = 1;
	
	/*Use DFS algorithm to search every node. And we create the trees.*/
	while(1){
		node_num = 0;
		if(vis[i] == 0){
		printf("i:%d\n",i);	
		DFS(i);
		}
		for(j=0;j<2*rows;j++){
			if(newpos[j] > 0) node_num++;
		}
		if(node_num == (2*rows)) break;
	i++;
	}
	printf("newpos\n");
	for(i=0;i<2*rows;i++){
		printf("%d ",newpos[i]);
	}
	printf("\n\n");
	printf("parent\n");
	for(i=0;i<2*rows;i++){
		printf("%d ",parent[i]);
	}
	printf("\n\n");
	MVC = 0;
	MVC = min_vertex_cover();
	/*In graph theory, minimum vertex cover is equivalent to maximum matching.
		If MVC is equal to the number of rows(columns), this program will stop.
	*/
	printf("set\n");
	for(i=0;i<2*rows;i++){
		printf("%d ",set[i]);
	}
	printf("\n");
	if(MVC == rows){printf("Minimum Vertex Cover is:%d\n",MVC);goto Exit;}
	min = INF;
	printf("\n");
	/*apply Köning’s graph theorem.*/
	for(i = 0;i < rows; i++){
		for(j = 0; j < cols; j++){
			if(set[i] != 1 && set[j+cols] != 1){
				printf("i:%d j:%d\n",i,j);
				//sleep(3);
				if(min > matrix[i][j]) min = matrix[i][j];
			}
		}
	}
	for(i = 0;i < rows; i++){
		for(j = 0; j < cols; j++){
			if(set[i] == 1 && set[j + cols] == 1){
				matrix[i][j] += min;
			}
			if(set[i] != 1 && set[j + cols] != 1){
				matrix[i][j] -= min;
			}
		}
	}
	printf("matrix\n");
	for(i=0;i<2*rows;i++){
		for(j=0;j<2*cols;j++){
			printf("%d ",test[i][j]);
		}
		printf("\n");
	}
	//sleep(3);
	/*********end*******/
	goto iteration;

	Exit:
	printf("matrix\n");
	for(i=0;i<2*rows;i++){
		for(j=0;j<2*cols;j++){
			printf("%d ",test[i][j]);
		}
		printf("\n");
	}
	printf("The following node is colored.\n");
	printf("node ");
	for(i=1;i<2*rows+1;i++){
		printf("%d ",i);
	}
	printf("\n");
	printf("     ");
	for(i=0;i<2*rows;i++){
		printf("%d ",set[i]);
	}
	printf("\n");
	printf("Mapping Matrix.\n");
	for(i = 1;i < rows+1; i++){
		for(j = 1; j < cols+1; j++){
			printf("%d ",map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for(i=rows+1;i<2*rows+1;i++){
		memset(vis,0,sizeof(vis));
		if(max_match(i)) ans++;
	}
	printf("max_matching:%d\n",ans);
	for(i=1;i<rows+1;i++){
		if(match[i] != 0)printf("%d match %d\n",i,match[i]);
	}
	printf("for example:");
	printf("\nIf the program shows that '1 match 6', '2 match 4', '3 match 5'\nmeans that node 1 match node 6, node 2 match node 4, node 3 match node 5. \n");
	printf("n  1 2 3\n");
	printf("4 {1,1,0}\n");
	printf("5 {0,0,1}\n");
	printf("6 {1,0,0}\n");
	/*For this program: the node number sequence is as following
		for example, the mapping function: 
	node_num 1 2 3
		  4 {1,1,0}
		  5 {0,0,1}
		  6 {1,0,0}
	so, if the program shows that '1 match 6', '2 match 4', '3 match 5'
	     means that node 1 match node 6, node 2 match node 4, node 3 match node 5. 
	*/
	
} 
