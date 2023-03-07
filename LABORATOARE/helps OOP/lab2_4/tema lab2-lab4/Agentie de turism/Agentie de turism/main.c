#include <stdio.h>
#include "ui.h"
#include <string.h>
#pragma warning(disable:4996)

int main()
{
	Service service;
	service.list_offer.lng = 0;
	UI program;
	program.service = service;

	run(program);
}
