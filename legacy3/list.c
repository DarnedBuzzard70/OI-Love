/*
想起了“早睡早起（早上六点睡早上八点起）”的学长，深夜有感：

Coding late at night feels like wandering alone into a quiet digital forest. 
The city outside fades from the hustle and bustle of daytime, 
leaving only the cold glow of the screen reflecting on my fingertips. 
The sound of keyboard taps becomes the sole melody, 
so clear you can hear the rebound of each key press.

At this moment, 
the mind grows unusually pure—no meeting interruptions, 
no message bombardments. 
It’s as if the brain has been switched to focus mode, 
climbing step by step along the vines of logic. 
When encountering a bug, 
the world suddenly shrinks to that single line of error code. 
The repetitive debugging process may seem tedious, 
yet it hides the thrill of solving a puzzle. 
The moment the breakpoint hits and the program runs smoothly, 
the exhaustion of the early morning is swept away by a sudden sense of accomplishment, 
as if the entire night has lit a light just for you.

Occasionally, I pause my typing, 
staring blankly at the flowing characters on the screen. 
The stillness of the night comes with a natural filter, softening complex logic. 
Problems that once felt tangled gradually reveal the outline of their solutions amid the silence. 
The steam from the coffee curls gently, 
intertwining with the blue light of the screen—becoming the most tacit companion to late-night coding.

It’s not until the sky lightens in the east and the code takes shape that I’m startled to realize the night has passed. 
Though my eyelids feel heavy, 
looking at the fully functional program fills my heart with solidity. 
Those nights stayed up, 
those pitfalls stumbled over—all eventually transform into marks of growth, 
quiet yet powerful.

Now, you are here, shining in the star light.
I brave the darkness from my innner world, 
"Thalium, I love you!"
looking for the light that shines through the darkness.
*/
#include <stdio.h>
#include <stdlib.h>
static inline int read_int() {
    int s = 0, w = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        s = 10 * s + ch - '0';
        ch = getchar();
    }
    return s * w;
}
typedef struct Node {
    int xuhao;
    int number;
    struct Node* next;
} Node;
Node* create_node(int xuhao, int number) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->xuhao = xuhao;
    new_node->number = number;
    new_node->next = NULL;
    return new_node;
}
Node* init_list() {
    Node* head = NULL;
    Node* tail = NULL;
    int num, count = 1;

    while (1) {
        num = read_int();
        if (num == 0) {
			break;
		}
        Node* new_node = create_node(count++, num);
        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }
    return head;
}
void print_list(Node* head) {
    Node* p = head;
    if (p == NULL) {
		return;
	}
    printf("%d", p->number);
    p = p->next;
    while (p != NULL) {
        printf(" %d", p->number);
        p = p->next;
    }
    printf("\n");
}
Node* find_by_xuhao(Node* head, int n) {
    Node* p = head;
    while (p != NULL) {
        if (p->xuhao == n) {
			return p;
		}
        p = p->next;
    }
    return NULL;
}
Node* find_by_number(Node* head, int x) {
    Node* p = head;
    while (p != NULL) {
        if (p->number == x) {
			return p;
		}
        p = p->next;
    }
    return NULL;
}
void update_xuhao(Node* head) {
    Node* p = head;
    int count = 1;
    while (p != NULL) {
        p->xuhao = count++;
        p = p->next;
    }
}
Node* insert_node(Node* head, int n, int x) {
    Node* target = find_by_xuhao(head, n);
    if (target == NULL) {
		return head;
	}
    Node* new_node = create_node(0, x);
    new_node->next = target->next;
    target->next = new_node;

    update_xuhao(head);
    return head;
}
Node* delete_node(Node* head, int n) {
    Node* target = find_by_xuhao(head, n);
    if (target == NULL) {
		return head;
	}
    Node* prev = NULL;
    Node* p = head;
    while (p != NULL && p != target) {
        prev = p;
        p = p->next;
    }
    if (prev == NULL) {
        head = target->next;
    } else {
        prev->next = target->next;
    }

    free(target);
    update_xuhao(head);
    return head;
}
void free_list(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node* head = init_list();
    print_list(head);
    int n = read_int();
    Node* node = find_by_xuhao(head, n);
    if (node != NULL) {
        printf("%d\n", node->number);
    }
    int x = read_int();
    node = find_by_number(head, x);
    if (node != NULL) {
        printf("%d %d\n", node->xuhao, node->number);
    }
    int insert_n = read_int();
    int insert_x = read_int();
    head = insert_node(head, insert_n, insert_x);
    print_list(head);
    int delete_n = read_int();
    head = delete_node(head, delete_n);
    print_list(head);
    free_list(head);
    return 0;
}
