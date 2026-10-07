//SLIP - 14
//Q.1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
    char name[50], phone[15];
    struct node *left,*right;
};

// Create
struct node* create(char name[],char phone[]){
    struct node* t=(struct node*)malloc(sizeof(struct node));
    strcpy(t->name,name);
    strcpy(t->phone,phone);
    t->left=t->right=NULL;
    return t;
}

// Insert
struct node* insert(struct node* root,char name[],char phone[]){
    if(root==NULL)
        return create(name,phone);

    if(strcmp(name,root->name)<0)
        root->left=insert(root->left,name,phone);
    else
        root->right=insert(root->right,name,phone);

    return root;
}

// Search
void search(struct node* root,char name[]){
    if(root==NULL){
        printf("Not Found\n");
        return;
    }

    int cmp = strcmp(name,root->name);

    if(cmp==0)
        printf("Found: %s %s\n",root->name,root->phone);
    else if(cmp<0)
        search(root->left,name);
    else
        search(root->right,name);
}

// Display
void inorder(struct node* root){
    if(root){
        inorder(root->left);
        printf("%s %s\n",root->name,root->phone);
        inorder(root->right);
    }
}

// Main
int main(){
    struct node* root=NULL;
    int ch;
    char name[50], phone[15];

    do{
        printf("\n1.Insert\n2.Search\n3.Display\n4.Exit\n");
        scanf("%d",&ch);

        switch(ch){
            case 1:
                scanf("%s %s",name,phone);
                root=insert(root,name,phone);
                break;

            case 2:
                scanf("%s",name);
                search(root,name);
                break;

            case 3:
                inorder(root);
                break;
        }
    }while(ch!=4);

    return 0;
}

//Q.2 - DBMS
// DBMS
//CREATE TABLE 
CREATE TABLE PROJECT (
 pno INT PRIMARY KEY,
 p_name CHAR(30),
 ptype CHAR(20),
 duration INT
);

CREATE TABLE EMPLOYEE (
 eno INT PRIMARY KEY,
 e_name CHAR(20),
 qualification CHAR(15),
 joindate DATE
);

-- M-M RELATION
CREATE TABLE PROJECT_EMPLOYEE (
 pno INT REFERENCES PROJECT(pno),
 eno INT REFERENCES EMPLOYEE(eno),
 start_date DATE,
 no_of_hours_worked INT,
 PRIMARY KEY(pno, eno)
);

//INSERT VALUES 
INSERT INTO PROJECT VALUES
(1,'AI System','Software',12),
(2,'Web App','IT',6);

INSERT INTO EMPLOYEE VALUES
(101,'Om','BSc','2022-01-01'),
(102,'Amit','MSc','2021-05-10');

INSERT INTO PROJECT_EMPLOYEE VALUES
(1,101,'2023-01-01',100),
(2,102,'2023-02-01',80);

//TRIGGER
CREATE OR REPLACE FUNCTION check_duration()
RETURNS trigger AS $$
BEGIN
 IF NEW.duration <= 0 THEN
  RAISE EXCEPTION 'Duration must be greater than zero';
 END IF;

 RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_project
BEFORE INSERT ON PROJECT
FOR EACH ROW
EXECUTE FUNCTION check_duration();

//Q.2 - PROCEDURE DBMS 
CREATE OR REPLACE PROCEDURE insert_project(
 pno INT,
 pname CHAR,
 ptype CHAR,
 duration INT
)
AS $$
BEGIN
 INSERT INTO PROJECT VALUES(pno, pname, ptype, duration);
 RAISE NOTICE 'Project inserted successfully';
END;
$$ LANGUAGE plpgsql;
