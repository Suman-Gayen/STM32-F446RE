

#ifndef DEMO_H_
#define DEMO_H_

//example
/*
 * data = 3E = 00111110
 * 		0x01 = 00000001
 * 		   & = 00000000
 *  */
void PrintData(unsigned char data){
	// zeroth bit
	if(data & 0x01 == 0x01){ /*turn on the pin representing bit zero*/ }// 0x01 = 00000001
	else 				   { /*turn 0ff the pin representing bit zero*/}

	// first bit
	if(data & 0x02 == 0x02){ /*turn on the pin representing bit first*/ }// 0x02 = 00000010
	else 				   { /*turn 0ff the pin representing bit first*/}

	// second bit
	if(data & 0x04 == 0x04){ /*turn on the pin representing bit second*/ }// 0x04 = 000000100
	else 				   { /*turn 0ff the pin representing bit second*/}

	// third bit
	if(data & 0x08 == 0x08){ /*turn on the pin representing bit third*/ }// 0x08 = 00001000
	else 				   { /*turn 0ff the pin representing bit third*/}

	// fourth bit
	if(data & 0x10 == 0x10){ /*turn on the pin representing bit fourth*/ }// 0x10 = 00010000
	else 				   { /*turn 0ff the pin representing bit fourth*/}

	// fifth bit
	if(data & 0x20 == 0x20){ /*turn on the pin representing bit fifth*/ }// 0x20 = 00100000
	else 				   { /*turn 0ff the pin representing bit fifth*/}

	// sixth bit
	if(data & 0x40 == 0x40){ /*turn on the pin representing bit sixth*/ }// 0x40 = 01000000
	else 				   { /*turn 0ff the pin representing bit sixth*/}

	// seven bit
	if(data & 0x80 == 0x80){ /*turn on the pin representing bit seven*/ }// 0x80= 10000000
	else 				   { /*turn 0ff the pin representing bit seven*/}

}

#endif /* DEMO_H_ */
