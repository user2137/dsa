//SLIP - 11
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

int count(struct node* root){
    if(root==NULL) return 0;
    return 1 + count(root->left) + count(root->right);
}

int countLeaf(struct node* root){
    if(root==NULL) return 0;
    if(root->left==NULL && root->right==NULL)
        return 1;
    return countLeaf(root->left) + countLeaf(root->right);
}

int main(){
    struct node* root=NULL;
    int n,val;

    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&val);
        root=insert(root,val);
    }

    printf("Total Nodes=%d\n",count(root));
    printf("Leaf Nodes=%d\n",countLeaf(root));
}

//Q.2 - DBMS
// DBMS
//CREATE TABLE 
CREATE TABLE Student (
 rollno INT PRIMARY KEY,
 s_name VARCHAR(20),
 class VARCHAR(10)
);

CREATE TABLE Subject (
 scode VARCHAR(10) PRIMARY KEY,
 subject_name VARCHAR(20)
);

-- M-M RELATION
CREATE TABLE Student_Subject (
 rollno INT REFERENCES Student(rollno),
 scode VARCHAR(10) REFERENCES Subject(scode),
 marks INT,
 PRIMARY KEY(rollno, scode)
);

//INSERT VALUES 
INSERT INTO Student VALUES
(1,'Om','SY'),
(2,'Amit','FY');

INSERT INTO Subject VALUES
('S1','DBMS'),
('S2','DS');

INSERT INTO Student_Subject VALUES
(1,'S1',80),
(1,'S2',70),
(2,'S1',60),
(2,'S2',50);

//TRIGGER
CREATE OR REPLACE FUNCTION delete_student_msg()
RETURNS trigger AS $$
BEGIN
 RAISE NOTICE 'student record is being deleted';
 RETURN OLD;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_student_delete
BEFORE DELETE ON Student
FOR EACH ROW
EXECUTE FUNCTION delete_student_msg();


//Q.2 - PROCEDURE DBMS 
CREATE OR REPLACE PROCEDURE sum_avg(n INT)
AS $$
DECLARE
 i INT := 1;
 s INT := 0;
 avg_val NUMERIC;
BEGIN
 WHILE i <= n LOOP
  s := s + i;
  i := i + 1;
 END LOOP;

 avg_val := s::NUMERIC / n;

 RAISE NOTICE 'Sum = %', s;
 RAISE NOTICE 'Average = %', avg_val;
END;
$$ LANGUAGE plpgsql;
