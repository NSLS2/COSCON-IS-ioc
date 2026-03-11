#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <dbAccess.h>
#include <dbDefs.h>
#include <dbFldTypes.h>
#include <registryFunction.h>
#include <subRecord.h>
#include <aSubRecord.h>
#include <epicsExport.h>
#include <recGbl.h>
#include <epicsTime.h>
#include <alarm.h>
#include <errlog.h>
#include <dbScan.h>
#include <link.h>

#define SHORT_STRAIGHT	6
#define LONG_STRAIGHT	8.7
#define CELL_LENGTH	19

int subDebug = 0;

static long aSub_R4K_80_STS_Init(aSubRecord* pasub)
{
    short flags = 0;   
	if (subDebug)
        	printf("Record %s called aSubMKSPrReadInit(%p)\n",pasub->name, (void*) pasub);
    
    memcpy((short *)pasub->vala, &flags, pasub->nova*sizeof(short));

	return 0;
}


// Status bits:
// Bit 0:  CF - Output cut off status
// Bit 1:  CO - Output enable status
// Bit 2:  LO - Local mode
// Bit 3:  RM - Remote mode
// Bit 4:  CC - Constant current mode
// Bit 5:  CV - Constant voltage mode
// Bit 6:  OVP - Over voltage protection
// Bit 7:  OCP - Over current protection
// Bit 8:  OT - Over temperature protection
// Bit 9:  ACF - AC input fault
// Bit 10: RS - Sense reverse connect
// Bit 11: LD - Inter Lock off
static long aSub_R4K_80_STS_Proc(aSubRecord* pasub)
{

    char status_codes[12][4] = {
        "CF", "CO", "LO", "RM", "CC", "CV",
        "OVP", "OCP", "OT", "ACF", "RS", "LD"
    }; 
    char *aptr = NULL;
    short flags = 0, mask=0x0001;

	if (subDebug)
        	printf("Record %s called aSubMKSPrReadInit(%p)\n",pasub->name, (void*) pasub);

    aptr = (char *)pasub->a;
    for(int i=0; i<12; i++) {
        if (strstr(aptr, status_codes[i]) != NULL) {
            flags |= mask;
        }
        mask <<= 1;
    }

    memcpy((short *)pasub->vala, &flags, pasub->nova*sizeof(short));

	return 0;
}


/* Register these symbols for use by IOC code: */
epicsExportAddress(int, subDebug);
epicsRegisterFunction(aSub_R4K_80_STS_Init);
epicsRegisterFunction(aSub_R4K_80_STS_Proc);


// static long aSubMKSPrReadInit(aSubRecord* pasub)
// {
// 	if (subDebug)
//         	printf("Record %s called aSubMKSPrReadInit(%p)\n",pasub->name, (void*) pasub);

// 	return 0;
// }

// static long aSubMKSPrReadProc(aSubRecord *pasub)
// {
// 	char *aptr;
// 	double prVal = 0;
// 	short prSts = 0;
// 	int len;

// 	/* Get the response from device */
// 	aptr = (char *)pasub->a;
// 	if(strcmp(aptr, "\0")== 0)
// 		return (0);

// 	len = strlen(aptr);

// 	if (subDebug)
// 		printf("Pressure status is %s \n", aptr);

// 	/* Check if there's a pressure reading */
// 	if(aptr[1] == '.')
// 	{
// 		prVal = atof(aptr);
// 		prSts = 0;
// 	}

// 	else if (strcmp(aptr, "LO<E-11") == 0 )
// 		prSts = 1;

// 	else if (strcmp(aptr, "LO<E-04") == 0 )
// 		prSts = 2;

// 	else if (strcmp(aptr, "LO<E-03") == 0 )
// 		prSts = 3;

// 	else if (strcmp(aptr, "ATM") == 0 )
// 		prSts = 4;

// 	else if (strcmp(aptr, "OFF") == 0 )
// 		prSts = 5;

// 	else if (strcmp(aptr, "RP_OFF") == 0 )
// 		prSts = 6;

// 	else if (strcmp(aptr, "WAIT") == 0 )
// 		prSts = 7;

// 	else if (strcmp(aptr, "CTRL_OFF") == 0 )
// 		prSts = 8;

// 	else if (strcmp(aptr, "PROT_OFF") == 0 )
// 		prSts = 9;

// 	else if (strcmp(aptr, "MISCONN") == 0 )
// 		prSts = 10;

// 	else if (strcmp(aptr, "NOGAUGE") == 0 )
// 		prSts = 11;

// 	else
// 	{
//  	  	recGblSetSevr(pasub, CALC_ALARM, INVALID_ALARM);
//    	 	return 0;
// 	}

// 	memcpy((double *)pasub->vala, &prVal, pasub->nova*sizeof(double));
// 	memcpy((short *)pasub->valb, &prSts, pasub->novb*sizeof(short));

// 	memset(aptr, 0, len*sizeof(char));

// 	pasub->pact = FALSE;

// 	return(0);
// }
