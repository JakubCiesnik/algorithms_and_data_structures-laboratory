#include <stdlib.h> 

// Currently have no idea what this does, just copy pasted from pseudo-code.txt

struct tree {
  int info;
	struct tree *left;
	struct tree *right;
};

// --------------------------------------------------budowa drzewa
struct tree *insert(struct tree *root, int x) {
	if(!root) {
		root=(struct tree*)malloc(sizeof(struct tree));
		root->info = x;
		root->left = NULL;
		root->right = NULL;
		return(root);
	}
  if(root->info > x)
	     root->left = insert(root->left,x);
  else if(root->info < x)
			root->right = insert(root->right,x);
	
	return(root);
}
// ------------------------------- może się przydac do szukania ale trzeba przerobić

// struct tree *search(struct tree *root, int x) {
// 	struct tree *ptr;
// 	ptr=root;
// 	while(ptr) {
// 		if(x>ptr->info)
// 		     ptr=ptr->right; else if(x<ptr->info)
// 		     ptr=ptr->left; else
// 		     break;
// 	}
// }
