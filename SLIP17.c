//SLIP - 17
//Q.1
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left, *right;
};

struct node* insert(struct node* root, int data){
    if(root==NULL){
        struct node* n = malloc(sizeof(struct node));
        n->data=data; n->left=n->right=NULL;
        return n;
    }
    if(data < root->data)
        root->left = insert(root->left,data);
    else
        root->right = insert(root->right,data);

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

//Q.2 - DBMS
// DBMS
//CREATE TABLE 

CREATE TABLE STUDENT (
 sreg_no INT PRIMARY KEY,
 name CHAR(30),
 class CHAR(10)
);

CREATE TABLE COMPETITION (
 c_no INT PRIMARY KEY,
 name CHAR(20),
 c_type CHAR(15)
);

-- M-M RELATION
CREATE TABLE STUDENT_COMPETITION (
 sreg_no INT REFERENCES STUDENT(sreg_no),
 c_no INT REFERENCES COMPETITION(c_no),
 rank INT,
 year INT,
 prize INT,
 PRIMARY KEY(sreg_no, c_no)
);


//INSERT VALUES 

INSERT INTO STUDENT VALUES
(1,'Om','SY'),
(2,'Amit','FY');

INSERT INTO COMPETITION VALUES
(101,'Quiz','academic'),
(102,'Cricket','sport');

INSERT INTO STUDENT_COMPETITION VALUES
(1,101,1,2020,5000),
(1,102,2,2020,2000),
(2,101,3,2021,1000);

//TRIGGER
CREATE OR REPLACE FUNCTION comp_update_msg()
RETURNS trigger AS $$
BEGIN
 RAISE NOTICE 'competition record is being updated';
 RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_comp
BEFORE UPDATE ON COMPETITION
FOR EACH ROW
EXECUTE FUNCTION comp_update_msg();

//Q.2 - PROCEDURE DBMS 
CREATE OR REPLACE PROCEDURE sum_50()
AS $$
DECLARE
 i INT := 1;
 s INT := 0;
BEGIN
 WHILE i <= 50 LOOP
  s := s + i;
  i := i + 1;
 END LOOP;

 RAISE NOTICE 'Sum = %', s;
END;
$$ LANGUAGE plpgsql;
