AvlTree avl_doubleRolateLeft(AvlPosition p){
	AvlPosition k1,k2,k3,k;
	k3 = p;
	k2 = k1->left;
	k1 = k2->right;

	k3->left = k1->right;
	k2->right = k1->left;
	k1->left = k2;
	k1->right = k3;
	k2->height = max(avl_height(k2->left,k2->right)) + 1;
	k3->height = max(avl_height(k3->left,k3->right)) + 1;
	k1->height = max(avl_height(k1->left,k1->right)) + 1;
	return k1;
}
