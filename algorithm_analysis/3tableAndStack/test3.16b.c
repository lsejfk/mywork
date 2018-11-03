
void rm_same(List L){
	Position p,q,s;
	for(p=First(L);!IsLast(p);p=Advance(p)){
		for(q=Advance(p);!IsLast(p);){
			if(Retrieve(p) == Retrieve(q)){
				s = Advance(q);
				Delete(q);
				q = s;
			}else{
				q = Advance(q);
			}
		}
	}
}
