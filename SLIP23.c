//SLIP - 23
//Q.1
#include <stdio.h>
#include <stdlib.h>

struct Node{
 int data;
 struct Node *left,*right;
};

int height(struct Node* root){
 if(root==NULL) return 0;

 int l=height(root->left);
 int r=height(root->right);

 return (l>r?l:r)+1;
}

int isBalanced(struct Node* root){
 if(root==NULL) return 1;

 int l=height(root->left);
 int r=height(root->right);

 if(abs(l-r)<=1 && isBalanced(root->left) && isBalanced(root->right))
  return 1;

 return 0;
}

//Q.2 - DBMS
// DBMS
//CREATE TABLE 

CREATE TABLE Car(
 c_no INT PRIMARY KEY,
 owner VARCHAR(20),
 model VARCHAR(10),
 color VARCHAR(10)
);

CREATE TABLE Driver(
 driver_no INT PRIMARY KEY,
 driver_name VARCHAR(20),
 license_no INT,
 d_age INT,
 salary FLOAT
);

CREATE TABLE Car_Driver(
 c_no INT REFERENCES Car(c_no),
 driver_no INT REFERENCES Driver(driver_no),
 PRIMARY KEY(c_no,driver_no)
);

//INSERT VALUES 

INSERT INTO Car VALUES
(1,'Amit','Swift','Red'),
(2,'Ravi','i20','Blue');

INSERT INTO Driver VALUES
(101,'Suresh',1111,25,20000),
(102,'Mahesh',2222,30,25000);

INSERT INTO Car_Driver VALUES
(1,101),
(2,101),
(2,102);

//CURSOR 

CREATE OR REPLACE PROCEDURE car_details(dname VARCHAR)
LANGUAGE plpgsql AS $$
DECLARE
 rec RECORD;
BEGIN
 FOR rec IN
  SELECT c.* FROM Car c
  JOIN Car_Driver cd ON c.c_no=cd.c_no
  JOIN Driver d ON d.driver_no=cd.driver_no
  WHERE d.driver_name=dname
 LOOP
  RAISE NOTICE '% % % %',rec.c_no,rec.owner,rec.model,rec.color;
 END LOOP;
END;
$$;

//Q.2 - PROCEDURE DBMS 
CREATE OR REPLACE PROCEDURE sum100()
LANGUAGE plpgsql AS $$
DECLARE i INT:=1;
s INT:=0;
BEGIN
 LOOP
  s:=s+i;
  i:=i+1;
  EXIT WHEN i>100;
 END LOOP;

 RAISE NOTICE 'Sum=%',s;
END;
$$;