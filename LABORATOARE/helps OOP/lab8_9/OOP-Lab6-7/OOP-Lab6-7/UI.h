#pragma once
#include "service.h"

class Console {
private:
	ActivitateStore& srv;

public:
	Console(ActivitateStore& srv) : srv{ srv } {};
	
	Console(const Console& ot) = delete;

	void print_meniu();
	void ui_add();
	void ui_delete();
	void ui_modify();
	void ui_find();
	void ui_filter();
	void ui_sort();
	void print_all_activities( VectorDinamic<Activitate> allActivities);
	void run();
};