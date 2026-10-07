//SLIP - 5
//Q.1

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left, *right;
};

// Create node
struct node* create(int val){
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = val;
    temp->left = temp->right = NULL;
    return temp;
}

// Insert in BST
struct node* insert(struct node* root, int val){
    if(root == NULL)
        return create(val);

    if(val < root->data)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);

    return root;
}

// Height of tree
int height(struct node* root){
    if(root == NULL)
        return 0;

    int l = height(root->left);
    int r = height(root->right);

    return (l > r ? l : r) + 1;
}

// Print nodes at given level
void printLevel(struct node* root, int level){
    if(root == NULL)
        return;

    if(level == 1)
        printf("%d ", root->data);
    else {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}

// Count nodes at given level
int countLevel(struct node* root, int level){
    if(root == NULL)
        return 0;

    if(level == 1)
        return 1;

    return countLevel(root->left, level - 1) + 
           countLevel(root->right, level - 1);
}

// Main
int main(){
    struct node* root = NULL;
    int n, val;

    printf("Enter number of nodes: ");
    scanf("%d",&n);

    printf("Enter values:\n");
    for(int i = 0; i < n; i++){
        scanf("%d",&val);
        root = insert(root, val);
    }

    int h = height(root);

    printf("\nTotal Levels = %d\n", h);

    for(int i = 1; i <= h; i++){
        printf("Level %d: ", i);
        printLevel(root, i);

        printf("\nCount = %d\n", countLevel(root, i));
    }

    return 0;
}

//Q.2 - DBMS
// DBMS
//CREATE TABLE 
CREATE TABLE Student (
 sreg_no INT PRIMARY KEY,
 s_name VARCHAR(20),
 s_class CHAR(10)
);

CREATE TABLE Competition (
 c_no INT PRIMARY KEY,
 c_name VARCHAR(20),
 c_type CHAR(10) NOT NULL CHECK (c_type IN ('sport','academic'))
);

-- M-M RELATION
CREATE TABLE Student_Competition (
 sreg_no INT REFERENCES Student(sreg_no),
 c_no INT REFERENCES Competition(c_no),
 rank INT,
 year INT,
 PRIMARY KEY(sreg_no, c_no)
);

//INSERT VALUES 
INSERT INTO Student VALUES
(1,'Om','SY'),
(2,'Amit','FY');

INSERT INTO Competition VALUES
(101,'Cricket','sport'),
(102,'Quiz','academic');

INSERT INTO Student_Competition VALUES
(1,101,1,2023),
(2,102,2,2023);

//TRIGGER
CREATE OR REPLACE FUNCTION comp_update_msg()
RETURNS trigger AS $$
BEGIN
 RAISE NOTICE 'competition record is being updated';
 RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_comp
BEFORE UPDATE ON Competition
FOR EACH ROW
EXECUTE FUNCTION comp_update_msg();


//Q.2 - PROCEDURE DBMS 
CREATE OR REPLACE PROCEDURE max_min(a INT, b INT, c INT)
AS $$
DECLARE
 mx INT;
 mn INT;
BEGIN
 mx := GREATEST(a,b,c);
 mn := LEAST(a,b,c);

 RAISE NOTICE 'Maximum = %', mx;
 RAISE NOTICE 'Minimum = %', mn;
END;
$$ LANGUAGE plpgsql;
