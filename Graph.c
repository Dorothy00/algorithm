#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTEX_NUM 20
#define MAX_VALUE_TYPE INT_MAX

typedef int VertexType;

typedef struct node
{
	VertexType adjvex;
	int weight;
	struct node *next;
}EdgeNode;

typedef struct vnode
{
	VertexType vertex;
	EdgeNode *first_edge;
}VertexNode;

typedef VertexNode AdjList[MAX_VERTEX_NUM];

typedef struct g
{
	AdjList adjlist;
	int vertex_num;
	int edge_num;
}Graph;

void CreateGraph(Graph *G);
void PrintGraph(Graph *G);
int MutiStageGragh(Graph *G, int k, int rout[]);

int main()
{
	Graph G;
	CreateGraph(&G);
	PrintGraph(&G);
	int k;
	printf("Please input Stage: ");
	scanf("%d", &k);
	int rout[k];
	int min_cost = MutiStageGragh(&G, k, rout);
	printf("Minmum cost is: %d", min_cost);
	printf("The rout is: ");
	for(int i = 0; i < k; i++)
	{
		printf("%d ", rout[i]);
	}
	return 0;
}

void CreateGraph(Graph *G)
{
	printf("Please input num of vertex and num of edge: ");
	scanf("%d%d", &G -> vertex_num, &G -> edge_num);

	for(int i = 0; i < G -> vertex_num; i++)
	{
		printf("Input vertex %d's value: ", i);
		scanf("%d", &G -> adjlist[i].vertex);
		G -> adjlist[i].first_edge = NULL;
	}
	EdgeNode *edge; 
	int start_node, end_node;
	for(int i = 0; i < G -> edge_num; i++)
	{
		edge = (EdgeNode*)malloc(sizeof(EdgeNode));
		printf("Input the edge's start node and end node: ");
		scanf("%d%d", &start_node, &end_node);
		printf("Input the edge's weight: ");
		scanf("%d", &edge -> weight);
		edge ->adjvex = end_node;
		edge -> next = G -> adjlist[start_node].first_edge;
		G -> adjlist[start_node].first_edge = edge;
	}
}

void PrintGraph(Graph *G)
{
	if(G == NULL)
	{
		return;
	}
	for(int i = 0; i < G -> vertex_num; i++)
	{
		printf("vertex[%d]", G -> adjlist[i].vertex);
		EdgeNode *edge = G -> adjlist[i].first_edge;
		while(edge != NULL)
		{
			printf("--%d--> vertex[%d]", edge -> weight, edge -> adjvex);
			edge = edge -> next;
		}
		printf("\n");
	}
}

int MutiStageGragh(Graph *G, int k, int rout[])
{
	int n = G -> vertex_num; 
	int cost[n];
	int d[n];
	cost[n - 1] = 0;
	d[n - 1] = n - 1;
	for(int i = n - 2; i >= 0; i--)
	{
		cost[i] = MAX_VALUE_TYPE;
		EdgeNode *edge = G -> adjlist[i].first_edge;
		while(edge != NULL)
		{
			if(edge -> weight + cost[edge -> adjvex] < cost[i])
			{
				cost[i] = edge -> weight + cost[edge -> adjvex];
				d[i] = edge -> adjvex;
			}
			edge = edge -> next;
		}
	}
	rout[0] = 0;
	rout[k - 1] = n - 1;
	for(int i = 1; i < k - 1; i++)
	{
		rout[i] = d[rout[i - 1]];
	}
	return cost[0];
}
