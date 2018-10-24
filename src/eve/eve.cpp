/*
* Copyright (c)2015 - 2016 Oasis LMF Limited 
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*
*   * Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in
*     the documentation and/or other materials provided with the
*     distribution.
*
*   * Neither the original author of this software nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
* THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*/

/*
eve: Event emitter for partioning work between multiple processes
Author: Ben Matharu  email: ben.matharu@oasislmf.org

*/


#include "../include/oasis.h"
#include <math.h>

extern char *progname;
namespace eve {
	void emitevents(OASIS_INT pno_, OASIS_INT total_)
	{
		FILE *fin = fopen(EVENTS_FILE, "rb");
		if (fin == NULL) {
			fprintf(stderr, "%s: %s: cannot open %s\n", progname, __func__, EVENTS_FILE);
			exit(EXIT_FAILURE);
		}
		fseek(fin, 0L, SEEK_END);
		long long  endpos = fltell(fin);

		int total_events = static_cast<OASIS_INT>(endpos / sizeof(OASIS_INT));
		int chunksize = (int)ceil((OASIS_FLOAT)total_events / total_);
		int end_pos = chunksize * pno_ * sizeof(OASIS_INT);
		pno_--;
		int start_pos = chunksize * pno_ * sizeof(OASIS_INT);
		fseek(fin, start_pos, SEEK_SET);
		while (start_pos < end_pos) {
			int c = fgetc(fin);
			if (c == EOF) break;
			fputc(c, stdout);
			start_pos++;
		}

		fclose(fin);
		return;

	}
}
