//SLIP - 1
//Q.1

#include <stdio.h>
#include <stdlib.h>

// Node structure
struct node
{
    int data;
    struct node *left, *right;
};

// Create node
struct node* create(int value)
{
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    temp->data = value;
    temp->left = temp->right = NULL;
    return temp;
}

// Insert
struct node* insert(struct node *root, int value)
{
    if(root == NULL)
        return create(value);

    if(value < root->data)
        root->left = insert(root->left, value);
    else if(value > root->data)
        root->right = insert(root->right, value);

    return root;
}

// Search
void search(struct node *root, int key)
{
    if(root == NULL)
    {
        printf("Not Found\n");
        return;
    }

    if(key == root->data)
        printf("Found\n");
    else if(key < root->data)
        search(root->left, key);
    else
        search(root->right, key);
}

// Traversals
void inorder(struct node *root)
{
    if(root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(struct node *root)
{
    if(root != NULL)
    {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct node *root)
{
    if(root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

// Main
int main()
{
    struct node *root = NULL;
    int ch, val;

    do
    {
        printf("\n1.Insert\n2.Search\n3.Inorder\n4.Preorder\n5.Postorder\n6.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch(ch)
        {
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                root = insert(root, val);
                break;

            case 2:
                printf("Enter value: ");
                scanf("%d", &val);
                search(root, val);
                break;

            case 3:
                inorder(root);
                break;

            case 4:
                preorder(root);
                break;

            case 5:
                postorder(root);
                break;
        }

    } while(ch != 6);

    return 0;
}

//Q.2 - DBMS

//Q.1 -DBMS
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

//STORED FUNCTION
CREATE OR REPLACE FUNCTION count_projects(emp_no INT)
RETURNS INT
AS $$
DECLARE cnt INT;
BEGIN
 SELECT COUNT(*) INTO cnt
 FROM Project_Employee
 WHERE eno = emp_no;

 RETURN cnt;
END;
$$ LANGUAGE plpgsql;

//Q.2 - PROCEDURE DBMS 
CREATE OR REPLACE PROCEDURE calc_three(a INT, b INT, c INT)
AS $$
BEGIN
 RAISE NOTICE 'Addition = %', a + b + c;
 RAISE NOTICE 'Subtraction = %', a - b - c;
 RAISE NOTICE 'Multiplication = %', a * b * c;
END;
$$ LANGUAGE plpgsql;
