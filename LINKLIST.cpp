#include<bits/stdc++.h>
using namespace std;

struct node {
	int data;
	struct node *next;
};

typedef struct node node;

node* makeNode(int x) {
	node *newNode = new node();
	newNode->data = x;
	newNode->next = NULL;
	return newNode;
}

void display(node *head) {
	while(head != NULL) {
		cout<<head->data<<" ";
		head = head->next;
	}
}

int size(node *head) {
	int cou = 0;
	while(head != NULL) {
		cou++;
		head = head->next;
	}
	return cou;
}

void pushFront(node *&head, int x) {
	node* newNode = makeNode(x);
	newNode->next = head;
	head = newNode;
}

void pushBack(node *&head, int x) {
	node* tmp = head;
	node* newNode = makeNode(x);
	if(tmp == NULL) {
		head = newNode;
		return;
	}
	while(tmp->next != NULL) {
		tmp = tmp->next;
	}
	tmp->next = newNode;
}

void insert(node *&head, int k, int x) {
	if(k == 1) {
		pushFront(head, x);
		return;
	}
	node *temp = head;
	node *newNode = makeNode(x);
	for(int i = 1; i < k-1; i++) {
		temp = temp->next;
	}
	newNode->next = temp->next;
	temp->next = newNode;
}

void popFront(node *&head) {
	if(head == NULL) {
		return;
	}
	node *temp = head;
	head = head->next;
	delete(temp);
}

void popBack(node *&head) {
	node* tmp = head;
	if(head == NULL) {
		return;
	}
	if(tmp->next == NULL) {
		head = NULL;
		delete(tmp);
		return;
	}
	while(tmp->next->next != NULL) {
		tmp = tmp->next;
	}
	tmp->next = NULL;
	delete(tmp->next);
}


void erase(node *&head, int k) {
	if(k == 1) {
		popFront(head);
		return;
	}
	node *temp = head;
	for(int i = 1; i <= k-2; i++) {
		temp = temp->next;
	}
	node* kth = temp->next;
	temp->next = kth->next;
	delete(kth);
}

//Bai 1

void deleteAllValue(node*& head, int a) {
    if (head == NULL) {
        return;
    }
    
    while (head != NULL && head->data == a) {
        node* temp = head;
        head = head->next;
        delete temp;
    }
    
    node* current = head;
    while (current != NULL && current->next != NULL) {
        if (current->next->data == a) {
            node* temp = current->next;
            current->next = temp->next;
            delete temp;
        } else {
            current = current->next;
        }
    }
}

//Bai 2

node* merge(node* list1, node* list2) {
    if (list1==NULL) {
        return list2;
    }
    if (list2 == NULL) {
        return list1;
    }
    
    node* result=NULL;
    
    if (list1->data <= list2->data) {
        result = list1;
        result->next = merge(list1->next, list2);
    } else {
        result = list2;
        result->next = merge(list1, list2->next);
    }
    
    return result;
}

//Bai 3:

node* mergeLists(vector<node*> lists, int l, int r) {
	if(r == l) {
		return lists[l];
	}
	int m = (r+l)/2;
	node* leftList = mergeLists(lists, l, m);
	node* rightList = mergeLists(lists, m, r);
	
	return merge(leftList, rightList);
}

node* merger32Lists(vector<node*> lists) {
	if (lists.empty()) {
        return nullptr;
    }
    
    int n = lists.size();
    
    while (n > 1) {
        int k = (n + 1) / 2;
        for (int i = 0; i < n / 2; i++) {
            lists[i] = merge(lists[i], lists[i + k]);
        }
        n = k;
    }
    
    return lists[0];
}




void testCase() {
	int n,m;
	//Bai 1
	cout<<"BAI 1:"<<endl;
	node* bai1 = NULL;
	cout<<"Nhap so luong phan tu: ";
	cin>>n;
	cout<<"Nhap "<<n<<" phan tu :";
	for(int i = 1; i <= n; i++) {
		int k;
		cin>>k;
		pushBack(bai1, k);
	}
	int a;
	cout<<"Nhap a: ";
	cin>>a;
	deleteAllValue(bai1, a);
	cout<<"Link list sau khi xoa nhung phan tu co gia tri a: ";
	display(bai1);
	
	//Bai 2
	cout<<endl<<"BAI 2:"<<endl;
	node* list1 = NULL;
	node* list2 = NULL;
	cout<<"Nhap so luong phan tu list 1: ";
	cin>>n;
	cout<<"Nhap "<<n<<" phan tu list 1: ";
	for(int i = 1; i <= n; i++) {
		int k;
		cin>>k;
		pushBack(list1, k);
	}
	cout<<"Nhap so luong phan tu list 2: ";
	cin>>m;
	cout<<"Nhap "<<n<<" phan tu list 2: ";
	for(int i = 1; i <= m; i++) {
		int k;
		cin>>k;
		pushBack(list2, k);
	}
	node* ans = merge(list1, list2);
	cout<<"Hop 2 list: ";
	display(ans);
	
	
	//Bai 3
	cout<<endl<<"BAI 3:"<<endl;
	
	vector<node*> lists;
	
	for(int i=0; i<32; i++) {
		//moi list 4 phan tu random
		node* list = NULL;
		for(int j=0; j<4; j++) {
			int k = rand() % 50;
			pushBack(list, k);
		}
		lists.push_back(list);
	}
	node* res = merger32Lists(lists);
	display(res);
}

int main() {
	int t;
	cout<<"Nhap so testCase: ";
	cin>>t;
	while(t--) {
		testCase();
		cout<<endl;
	}
}
