//SLIP - 19
//Q.1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
 char name[50];
 char phone[15];
 struct node *left,*right;
};

struct node* create(char name[], char phone[]){
 struct node* n = malloc(sizeof(struct node));
 strcpy(n->name,name);
 strcpy(n->phone,phone);
 n->left=n->right=NULL;
 return n;
}

struct node* insert(struct node* root,char name[],char phone[]){
 if(root==NULL)
  return create(name,phone);

 if(strcmp(name,root->name)<0)
  root->left=insert(root->left,name,phone);
 else if(strcmp(name,root->name)>0)
  root->right=insert(root->right,name,phone);

 return root;
}

void search(struct node* root,char name[]){
 if(root==NULL){
  printf("Not found\n");
  return;
 }

 int cmp = strcmp(name,root->name);

 if(cmp==0)
  printf("Name:%s Phone:%s\n",root->name,root->phone);
 else if(cmp<0)
  search(root->left,name);
 else
  search(root->right,name);
}

//Q.2 - DBMS
// DBMS
//CREATE TABLE 

CREATE TABLE Project (
 pno INT PRIMARY KEY,
 pname CHAR(30) NOT NULL,
 ptype CHAR(20),
 duration INT CHECK (duration > 0)
);

CREATE TABLE Employee (
 eno INT PRIMARY KEY,
 ename CHAR(20),
 qualification CHAR(15),
 joining_date DATE
);

-- M-M RELATION
CREATE TABLE Project_Employee (
 pno INT REFERENCES Project(pno),
 eno INT REFERENCES Employee(eno),
 start_date DATE,
 no_of_hours_worked INT,
 PRIMARY KEY(pno, eno)
);

//INSERT VALUES 

INSERT INTO Project VALUES
(1,'AI System','Software',12),
(2,'Web App','IT',6);

INSERT INTO Employee VALUES
(101,'Om','BSc','2022-01-01'),
(102,'Amit','MSc','2021-05-10');

INSERT INTO Project_Employee VALUES
(1,101,'2023-01-01',100),
(2,101,'2023-02-01',80),
(2,102,'2023-03-01',60);

//FUNCTION COUNT PROJECTS

CREATE OR REPLACE FUNCTION count_projects(eid INT)
RETURNS INT AS $$
DECLARE c INT;
BEGIN
 SELECT COUNT(*) INTO c
 FROM Project_Employee
 WHERE eno = eid;

 RETURN c;
END;
$$ LANGUAGE plpgsql;

//Q.2 - PROCEDURE DBMS 
CREATE OR REPLACE PROCEDURE min_max(a INT, b INT)
AS $$
DECLARE
 mn INT;
 mx INT;
BEGIN
 mn := LEAST(a,b);
 mx := GREATEST(a,b);

 RAISE NOTICE 'Minimum = %', mn;
 RAISE NOTICE 'Maximum = %', mx;
END;
$$ LANGUAGE plpgsql;
