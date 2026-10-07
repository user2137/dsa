//SLIP - 2
//Q.1

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left, *right;
};

struct node* create(int val) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = val;
    temp->left = temp->right = NULL;
    return temp;
}

struct node* insert(struct node* root, int val) {
    if(root == NULL)
        return create(val);

    if(val < root->data)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);

    return root;
}

void find_min(struct node* root) {
    while(root->left != NULL)
        root = root->left;

    printf("Min = %d\n", root->data);
}

void find_max(struct node* root) {
    while(root->right != NULL)
        root = root->right;

    printf("Max = %d\n", root->data);
}

int main() {
    struct node* root = NULL;
    int n, val;

    scanf("%d",&n);

    for(int i=0;i<n;i++) {
        scanf("%d",&val);
        root = insert(root,val);
    }

    find_min(root);
    find_max(root);

    return 0;
}

//Q.2 - DBMS
//CREATE TABLE
CREATE TABLE Area (
 aname VARCHAR(20) PRIMARY KEY,
 area_type VARCHAR(5) CHECK (area_type IN ('urban','rural'))
);

CREATE TABLE Person (
 pno INT PRIMARY KEY,
 pname VARCHAR(20),
 birthdate DATE,
 income MONEY,
 aname VARCHAR(20) REFERENCES Area(aname)
);

//INSERT VALUES 
INSERT INTO Area VALUES
('Pune','urban'),
('Village','rural');

INSERT INTO Person VALUES
(1,'Om','2000-01-01',50000,'Pune'),
(2,'Amit','1999-02-02',40000,'Village'),
(3,'Ravi','2001-03-03',60000,'Pune'); 
//STORED FUNCTION
CREATE OR REPLACE FUNCTION count_persons(area_name VARCHAR)
RETURNS INT
AS $$
DECLARE cnt INT;
BEGIN
 SELECT COUNT(*) INTO cnt
 FROM Person
 WHERE aname = area_name;

 RETURN cnt;
END;
$$ LANGUAGE plpgsql;

//Q.2 - PROCEDURE DBMS 
CREATE OR REPLACE PROCEDURE divide(a INT, b INT)
AS $$
BEGIN
 IF b = 0 THEN
  RAISE EXCEPTION 'Division by zero not allowed';
 ELSE
  RAISE NOTICE 'Division = %', a::NUMERIC / b;
 END IF;
END;
$$ LANGUAGE plpgsql;
