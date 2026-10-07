//SLIP - 18
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
        n->data=data;
        n->left=n->right=NULL;
        return n;
    }
    if(data < root->data)
        root->left = insert(root->left,data);
    else
        root->right = insert(root->right,data);
    return root;
}

int height(struct node* root){
    if(root==NULL) return 0;
    int lh = height(root->left);
    int rh = height(root->right);
    return (lh>rh?lh:rh)+1;
}

int isBalanced(struct node* root){
    if(root==NULL) return 1;
    int lh = height(root->left);
    int rh = height(root->right);

    if(abs(lh-rh)<=1 && isBalanced(root->left) && isBalanced(root->right))
        return 1;
    return 0;
}

//Q.2 - DBMS
// DBMS
//CREATE TABLE 
CREATE TABLE Item (
 itemno INT PRIMARY KEY,
 itemname VARCHAR(20)
);

CREATE TABLE Supplier (
 supplier_no INT PRIMARY KEY,
 supplier_name VARCHAR(20),
 city VARCHAR(20)
);

-- M-M RELATION
CREATE TABLE Item_Supplier (
 itemno INT REFERENCES Item(itemno),
 supplier_no INT REFERENCES Supplier(supplier_no),
 rate MONEY,
 quantity INT,
 PRIMARY KEY(itemno, supplier_no)
);

//INSERT VALUES 

INSERT INTO Item VALUES
(1,'Pen'),
(2,'Book');

INSERT INTO Supplier VALUES
(101,'ABC','Pune'),
(102,'XYZ','Mumbai');

INSERT INTO Item_Supplier VALUES
(1,101,600,10),
(2,102,300,20);

//TRIGGER
CREATE OR REPLACE FUNCTION check_rate()
RETURNS trigger AS $$
BEGIN
 IF NEW.rate < 50 THEN
  RAISE EXCEPTION 'Rate must be at least 50';
 END IF;

 RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_rate
BEFORE INSERT OR UPDATE ON Item_Supplier
FOR EACH ROW
EXECUTE FUNCTION check_rate();

//Q.2 - PROCEDURE DBMS 
CREATE OR REPLACE PROCEDURE max_num(a INT, b INT, c INT)
AS $$
DECLARE
 mx INT;
BEGIN
 mx := GREATEST(a,b,c);
 RAISE NOTICE 'Maximum = %', mx;
END;
$$ LANGUAGE plpgsql;
