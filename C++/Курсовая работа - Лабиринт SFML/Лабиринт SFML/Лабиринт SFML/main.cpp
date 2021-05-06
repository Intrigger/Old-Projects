#include<iostream>

using namespace std;

struct list;

struct Vertex{
    int x;
    int y;
    int color;
    int length;
    list *l;
};

struct list{
    Vertex *v;
    list* next;
};

void AppendVertex(list* &l, Vertex *v){
    if (l == nullptr){
        l = new list;
        l->v = v;
        l->next = nullptr;
    }
    else{
        list* cur = l;
        while (cur->next != nullptr){
            cur = cur->next;
        }
        cur->next = new list;
        cur = cur->next;
        cur->v = v;
        cur->next = nullptr;
    }
}

void PrintList(list* l){
    int cur = 0;
    while (l != nullptr){
        printf("[%d][%p] x:%d, y:%d, color:%d, length: %d\n", cur++, l->v ,l->v->x, l->v->y, l->v->color, l->v->length);
        if (l->next != nullptr) l = l->next;
        else break;
    }
}

int getListLength(list* l){
    int length = 0;
    if (l == nullptr) return 0;
    else{
        length = 1;
        while (l->next != nullptr){
            length++;
            l = l->next;
        }
        return length;
    }
}

void deleteFirst(list* &l){
    if (l == nullptr) return;
    if (getListLength(l) == 1) l = nullptr;
    else{
        list* newL = l->next;
        delete l;
        l = newL;
    }
}

bool inList(list* l, Vertex *v){
    if (l == nullptr) return false;
    while (l->next != nullptr){
        if (l->v == v){
            return true;
        }
        l = l->next;
    }
    if (l->v == v) return true;
    return false;
}

int main() {

    const int H = 10, W = 10;
    std::string fieldStr[H] = {
    "1111111111",
    "1011110001",
    "1000010001",
    "1000010001",
    "1000010001",
    "1000010001",
    "1001111001",
    "1000000001",
    "1000001001",
    "1111111111"
    };

    int startX = 1, startY = 1;

    auto *arr = new Vertex[H * W];

    for (int j = 0; j < H; j++){
        for (int i = 0; i < W; i++){
            if (fieldStr[j][i] != 1){
                arr[j * W + i] = {i, j, 0, INT32_MAX, nullptr};
            }
        }
    }

    list* l = nullptr;

    //Appending the 1-st vertex (starting vertex)
    arr[W * startY + startX].color = 1;
    AppendVertex(l, &arr[W*startY + 1]);


    int listLength = getListLength(l);

    list* current = l;

    for (int i = 0; i < listLength; i++){
        current = l;
        int curX = current->v->x;
        int curY = current->v->y;
        printf("CurX: %d, CurY: %d\n", curX, curY);
        //top
        if ((curY - 1 >= 0) && (fieldStr[curY - 1][curX] != '1')){
            if (arr[(curY-1) * W + curX].color != 2){
                arr[(curY-1) * W + curX].color = 1;
                if (!inList(current->v->l, &arr[(curY-1) * W + curX])){
                    AppendVertex(current->v->l, &arr[(curY-1) * W + curX]);
                    printf("adding top!\n");
                }
                if (!inList(arr[(curY-1) * W + curX].l, current->v)){
                    AppendVertex(arr[(curY-1) * W + curX].l, current->v);
                    printf("adding top!\n");
                }
                if (!inList(l, &arr[(curY-1) * W + curX])){
                    AppendVertex(l, &arr[(curY-1) * W + curX]);
                    printf("adding top to the list!\n");
                }
            }
        }
        if ((curY + 1 < H) && (fieldStr[curY + 1][curX] != '1')){
            if (arr[(curY+1) * W + curX].color != 2){
                arr[(curY+1) * W + curX].color = 1;
                if (!inList(current->v->l, &arr[(curY+1) * W + curX])){
                    AppendVertex(current->v->l, &arr[(curY+1) * W + curX]);
                    printf("adding bot!\n");
                }
                if (!inList(arr[(curY+1) * W + curX].l, current->v)){
                    AppendVertex(arr[(curY+1) * W + curX].l, current->v);
                    printf("adding bot!\n");
                }
                if (!inList(l, &arr[(curY+1) * W + curX])) {
                    AppendVertex(l, &arr[(curY + 1) * W + curX]);
                    printf("adding bot to the list!\n");
                }
            }
        }
        if ((curX - 1 >= 0) && (fieldStr[curY][curX - 1] != '1')){
            if (arr[curY * W + (curX - 1)].color != 2){

                arr[curY * W + (curX - 1)].color = 1;
                if (!inList(current->v->l, &arr[curY * W + (curX - 1)])) {
                    AppendVertex(current->v->l, &arr[curY * W + (curX - 1)]);
                    printf("adding left!\n");
                }
                if (!inList(arr[curY * W + (curX - 1)].l, current->v)) {
                    AppendVertex(arr[curY * W + (curX - 1)].l, current->v);
                    printf("adding left!\n");
                }
                if (!inList(l, &arr[curY * W + (curX - 1)])){
                    AppendVertex(l, &arr[curY * W + (curX - 1)]);
                    printf("adding left to the list!\n");
                }
            }
        }
        if ((curX + 1 < W) && (fieldStr[curY][curX + 1] != '1')){
            if (arr[curY * W + (curX + 1)].color != 2){

                arr[curY * W + (curX + 1)].color = 1;
                if (!inList(current->v->l, &arr[curY * W + (curX + 1)])) {
                    AppendVertex(current->v->l, &arr[curY * W + (curX + 1)]);
                    printf("adding right!\n");
                }
                if (!inList(arr[curY * W + (curX + 1)].l, current->v)) {
                    AppendVertex(arr[curY * W + (curX + 1)].l, current->v);
                    printf("adding right!\n");
                }
                if (!inList(l, &arr[curY * W + (curX + 1)])){
                    AppendVertex(l, &arr[curY * W + (curX + 1)]);
                    printf("adding right to the list!\n");
                }
            }
        }
        (*current->v).color = 2;
        deleteFirst(l);
        if (i == listLength - 1){
            i = -1;
            listLength = getListLength(l);
            current = l;
            PrintList(l);
        }
    }

    printf("Graph Built!\n");

    for (int j = 0; j < H; j++){
        for (int i = 0; i < W; i++){
            printf("Connections of %d (total %d):\n", j * W + i, getListLength(arr[j * W + i].l));
            PrintList(arr[j * W + i].l);
            printf("\n\n");
        }
    }

    for (int j = 0; j < H; j++){
        for (int i = 0; i < W; i++){
            if (fieldStr[j][i] != 1){
                arr[j * W + i].color = 0;
            }
        }
    }
    arr[W*startY + 1].color = 1;
    arr[W*startY + 1].length = 0;
    AppendVertex(l, &arr[W*startY + 1]);
    current = l;
    listLength = getListLength(l);
    for (int i = 0; i < listLength; i++){
        current = l;
        list* cur = current->v->l;
        while (cur != nullptr){
            (*cur->v).length = min(cur->v->length, current->v->length + 1);
            if ((!inList(l, cur->v)) && (cur->v->color != 2)){
                AppendVertex(l, cur->v);
            }
            cur = cur->next;
        }

        (*current->v).color = 2;
        deleteFirst(l);
        if (i == listLength - 1){
            i = -1;
            listLength = getListLength(l);
            current = l;
            PrintList(l);
            printf("\n");
        }
    }

    for (int j = 0; j < H; j++){
        for (int i = 0; i < W; i++){
            if (arr[j*W + i].length == INT32_MAX) printf("#\t");
            else printf("%d\t", arr[j*W + i].length);
        }
        printf("\n");
    }

    int destX = 8, destY = 8;

    Vertex *cur = &arr[destY * W + destX];
    list* path = nullptr;
    AppendVertex(path, cur);
    while (cur->length != 0){
        printf("%d connections\n", getListLength(cur->l));
        while (cur->l != nullptr){
            if (cur->l->v->length == cur->length - 1){
                AppendVertex(path, cur->l->v);
                cur = cur->l->v;
                break;
            }
            cur->l = cur->l->next;
        }
        printf("cur.length: %d\n", cur->length);
    }

    printf("Path: \n");
    PrintList(path);

	return 0;
}
