/**
 * The type of Tag that a word in a user-entered command will have:
 * Special:
 * 	ERR - reserved so that stack return an ERR on empty stack
 * 	INV - invalid
 * Terminals:
 * 	ADJ - adjevtive
 * 	ART - article
 * 	E - edge
 * 	N - noun
 * 	P - perposition
 * 	V - verb
 * Non-terminals:
 * 	C - command
 * 	VP - verb phrsae
 * 	NP - noun phrase
 * 	PP - prepositional phrase
 * 	EP - edge phrase
 * 	E_ - subdivision of edge phrase, used for "E" or "ADJ E_"
 * 	N_ - subdivision of noun phrase, used for "N" or "ADJ N_"
 */

#ifndef TAG_HPP
#define TAG_HPP
enum Tag { ERR = -1,
	INV, ADJ, ART, E, N, P, V, C, VP, NP, PP, EP, E_, N_  };
#endif
