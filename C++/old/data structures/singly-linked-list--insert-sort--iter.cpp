struct sll {
	sll * next;
	int id;
};

void add_sll(sll * & head, int id) {
	sll ** ptr = &head;
	sll * obj = new sll{head, id};
	head = obj;
	while ((*ptr)->next && (*ptr)->next->id > (*ptr)->id) {
		sll * head_cp = *ptr;
		*ptr = (*ptr)->next;
		head_cp->next = (*ptr)->next;
		(*ptr)->next = head_cp;
		ptr = &(*ptr)->next;
	}
}