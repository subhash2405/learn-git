#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// this is my assignment
FILE* fout;
int vertices = 0;
int edges;
int head=0;
int tail=0;

struct Node {
    int data;
    struct Node* next;
};

void insert_list(int a, int b, struct Node* adjlist[]);
void BFS(int x, struct Node* adjlist[], int distance[], int queue[]);
void enqueue(int element, int queue[]);
void dequeue(int queue[]);



//struct Node* adjlist[];

int main(int argc, char* argv[]) {
    FILE* fin;
    fin = fopen(argv[1], "r");
    fout = fopen("sd.txt", "w");

    if (fin == NULL) {
        printf("ERROR: input file not open\n");
        return 1;
    }

    int num;
    int vertex;
    fscanf(fin, "%d", &vertices);
    fscanf(fin, "%d", &edges);
    struct Node* adjlist[vertices];
    for (int i = 0; i < vertices; i++)
        adjlist[i] = NULL;
    
    int queue[vertices];
    int distance[vertices];
    

    while (fscanf(fin, "%d %d", &vertex, &num) != EOF) {
        insert_list(vertex, num, adjlist);
    }

    BFS(0, adjlist, distance, queue);

    for (int i = 0; i < vertices; i++) {
        if(distance[i]==0){
            fprintf(fout,"-1\n");
        }
        fprintf(fout, "%d\n", distance[i]);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}

//struct Node* adjlist[vertices];
void insert_list(int a, int b, struct Node* adjlist[]) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->data = b;
    newNode->next = adjlist[a];
    adjlist[a] = newNode;
}

int queuefull() {
    if (tail == vertices - 1) {
        return 1;
    }
    else {
        return 0;
    }
}

void enqueue(int element, int queue[]) {
    for (int i = 0; i < vertices; i++) {
        if (queue[i] == element) {
            return;
        }
    }
    if (!queuefull()) {
        tail++;
        queue[tail] = element;
        if (head == -1) {
            head++;
        }
    }
    else {
        printf("queue is full");
    }
}

int queue_empty() {
    if ((head == -1 && tail == -1) || (tail + 1 == head)) {
        return 1;
    }
    else {
        return 0;
    }
}

void dequeue(int queue[]) {
    if (!queue_empty()) {
        queue[head] = -1;
        head++;
    }
    else {
        printf("underflow"); //get a return condition
    }
}

void BFS(int x, struct Node* adjlist[], int distance[], int queue[]) {
    struct Node* temp = NULL;
    temp = adjlist[x];
    enqueue(x, queue);
    while (temp != NULL) {
        distance[temp->data] = distance[x] + 1;
        BFS(temp->data, adjlist, distance, queue);
        temp = temp->next;
    }
    dequeue(queue);
}
