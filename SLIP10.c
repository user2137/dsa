//SLIP - 10
//Q.1

#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *left,*right;
};

struct node* insert(struct node* root,int val){
    if(root==NULL){
        struct node* t=(struct node*)malloc(sizeof(struct node));
        t->data=val;
        t->left=t->right=NULL;
        return t;
    }
    if(val<root->data)
        root->left=insert(root->left,val);
    else
        root->right=insert(root->right,val);
    return root;
}

int findMin(struct node* root){
    while(root->left!=NULL)
        root=root->left;
    return root->data;
}

int findMax(struct node* root){
    while(root->right!=NULL)
        root=root->right;
    return root->data;
}

int main(){
    struct node* root=NULL;
    int n,val;

    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&val);
        root=insert(root,val);
    }

    printf("Min=%d\n",findMin(root));
    printf("Max=%d\n",findMax(root));
}

//Q.2 - DBMS
// DBMS
//CREATE TABLE 
CREATE TABLE Book (
 b_no INT PRIMARY KEY,
 b_name VARCHAR(20),
 pub_name VARCHAR(10) NOT NULL,
 b_price FLOAT
);

CREATE TABLE Author (
 a_no INT PRIMARY KEY,
 a_name VARCHAR(20),
 qualification VARCHAR(15),
 address VARCHAR(15)
);

-- M-M RELATION
CREATE TABLE Book_Author (
 b_no INT REFERENCES Book(b_no),
 a_no INT REFERENCES Author(a_no),
 PRIMARY KEY(b_no, a_no)
);

//INSERT VALUES 
INSERT INTO Book VALUES
(1,'DBMS','TechPub',1200),
(2,'C Lang','EduPub',500);

INSERT INTO Author VALUES
(101,'Ramesh','PhD','Pune'),
(102,'Suresh','MSc','Mumbai');

INSERT INTO Book_Author VALUES
(1,101),
(2,102);

//TRIGGER
CREATE OR REPLACE FUNCTION check_price()
RETURNS trigger AS $$
BEGIN
 IF NEW.b_price > 1000 THEN
  RAISE NOTICE 'Price is so high';
 END IF;

 RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_book
AFTER INSERT ON Book
FOR EACH ROW
EXECUTE FUNCTION check_price();

//Q.2 - PROCEDURE DBMS 
CREATE OR REPLACE PROCEDURE even_numbers()
AS $$
DECLARE
 i INT := 2;
BEGIN
 WHILE i <= 50 LOOP
  RAISE NOTICE '%', i;
  i := i + 2;
 END LOOP;
END;
$$ LANGUAGE plpgsql;

