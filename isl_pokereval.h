/* 
 isl_pokereval - v0.0.1 - single-header version of poker-eval GPLv3 C lib
                          no warranty implied; use at your own risk

 author: Ilya Kolbin (iskolbin@gmail.com)
 url: github.com:iskolbin/isl_pokereval

 Original authors:  
     Loic Dachary <loic@dachary.org>
     Tim Showalter <tjs@psaux.com> 
     Michael Maurer <mjmaurer@yahoo.com>

 Original software is distributed under GPLv3, from sources:
 This program gives you software freedom; you can copy, convey,
 propagate, redistribute and/or modify this program under the terms of
 the GNU General Public License (GPL) as published by the Free Software
 Foundation (FSF), either version 3 of the License, or (at your option)
 any later version of the GPL published by the FSF.

 This program is distributed in the hope that it will be useful, but
 WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 General Public License for more details.

 You should have received a copy of the GNU General Public License along
 with this program in a file in the toplevel directory called "GPLv3".
 If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ISL_INCLUDE_POKER_EVAL_H_
#define ISL_INCLUDE_POKER_EVAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

/* include/poker_defs.h */
/* Compiler-specific junk */

#if defined(_MSC_VER)
#  define UINT64_TYPE unsigned __int64
#  define inline __inline
#  define thread __declspec( thread )
#else
#  define thread 
#  ifndef WORDS_BIGENDIAN
/* Define if your processor stores words with the most significant
   byte first (like Motorola and SPARC, unlike Intel and VAX).  */
/* #undef WORDS_BIGENDIAN */
#  endif /* WORDS_BIGENDIAN */

#  ifndef HAVE_UINT64_T
/* Define if your compiler supports "uint64_t" for 64 bit integers */
#  define HAVE_UINT64_T 1
#  endif /* HAVE_UINT64_T */

#  ifndef HAVE_LONG_LONG
/* Define if your compiler supports "long long" for 64 bit integers */
#  define HAVE_LONG_LONG 1
#  endif /* HAVE_LONG_LONG */

#  ifndef HAVE_INT8
/* Define if type "int8" is defined already */
/* #undef HAVE_INT8 */
#  endif /* HAVE_INT8 */

#  ifndef SIZEOF_LONG
/* The size of a `long', as computed by sizeof. */
#  define SIZEOF_LONG 4
#  endif /* SIZEOF_LONG */

#  ifndef HAVE_INTTYPES_H
/* Check if we have/need the inttypes include file */
#  define HAVE_INTTYPES_H 1
#  endif /* HAVE_INTTYPES_H */

#  ifndef HAVE_STDINT_H
/* Check if we have/need the stdint include file */
#  define HAVE_STDINT_H 1
#  endif /* HAVE_STDINT_H */

#  ifndef HAVE_SYS_TYPES_H
/* Check if we have/need the sys/types include file */
#  define HAVE_SYS_TYPES_H 1
#  endif /* HAVE_SYS_TYPES_H */

#endif

#ifdef HAVE_SYS_TYPES_H
#  include <sys/types.h>
#endif
#ifdef HAVE_INTTYPES_H
#  include <inttypes.h>
#else
#  ifdef HAVE_STDINT_H
#    include <stdint.h>
#  endif
#endif

/* 64-bit integer junk */

#undef USE_INT64
#ifdef HAVE_UINT64_T
typedef uint64_t		uint64;
#define USE_INT64 1
#elif defined(HAVE_LONG_LONG)
typedef unsigned long long      uint64;
#define USE_INT64 1
#elif SIZEOF_LONG == 8
typedef unsigned long           uint64;
#define USE_INT64 1
#elif defined(UINT64_TYPE)
typedef UINT64_TYPE             uint64;
#define USE_INT64 1
#endif

#ifdef USE_INT64
#define LongLong_OP(result, op1, op2, operation) \
  do { result = (op1) operation (op2); } while (0)
#define LongLong_OR(result, op1, op2)  LongLong_OP(result, op1, op2, |)
#define LongLong_AND(result, op1, op2) LongLong_OP(result, op1, op2, &)
#define LongLong_XOR(result, op1, op2) LongLong_OP(result, op1, op2, ^)
#endif


typedef unsigned char  uint8;
#ifndef HAVE_INT8
typedef signed char   int8;
#endif
typedef unsigned short uint16;
typedef unsigned int   uint32;

/* include/poker_export.h */
#if defined(_MSC_VER)
    #pragma warning( disable : 4244 )
    #pragma warning( disable : 4251 )
    #pragma warning( disable : 4267 )
    #pragma warning( disable : 4275 )
    #pragma warning( disable : 4290 )
    #pragma warning( disable : 4786 )
    #pragma warning( disable : 4305 )
#endif

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
	#ifndef POKERVAL_DLL
		#ifdef __cplusplus
			#define POKEREVAL_EXPORT "C"
		#else
			#define POKEREVAL_EXPORT
		#endif
	#else
		#ifdef POKEREVAL_LIBRARY
			#ifdef __cplusplus
				#define POKEREVAL_EXPORT "C" __declspec(dllexport)
			#else
				#define POKEREVAL_EXPORT "C"
			#endif
		#else
			#ifdef __cplusplus
				#define POKEREVAL_EXPORT "C" __declspec(dllimport)
			#else
				#define POKEREVAL_EXPORT "C"
			#endif
		#endif
	#endif

#else
	#ifdef __cplusplus
		#define POKEREVAL_EXPORT "C"
	#else
		#define POKEREVAL_EXPORT
	#endif
#endif

/* include/deck.h */ 
typedef int     Deck_cardToStringFn(int cardIndex, char *outString);
typedef int     Deck_maskToCardsFn(void *cardMask, int cardIndices[]);
typedef int     Deck_stringToCardFn(char *inString, int *index);
typedef int     Deck_numCardsFn(void *cardMask);

typedef struct {
  int                  nCards;
  char *               name;
  Deck_cardToStringFn *cardToString;
  Deck_stringToCardFn *stringToCard;
  Deck_maskToCardsFn  *maskToCards;
  Deck_numCardsFn     *numCards;
} Deck;

#define Deck_cardToString       (CurDeck.cardToString)
#define Deck_stringToCard       (CurDeck.stringToCard)
#define Deck_cardString(i)      GenericDeck_cardString(&(CurDeck), (i))
#define Deck_printCard(i)       GenericDeck_printCard(&(CurDeck), (i))

#define Deck_printMask(m)       \
        GenericDeck_printMask(&CurDeck, ((void *) &(m)))

#define Deck_maskString(m)      \
        GenericDeck_maskString(&CurDeck, ((void *) &(m)))

#define Deck_numCards(m)      \
        GenericDeck_numCards(&CurDeck, ((void *) &(m)))

#define Deck_maskToString(m, s) \
        GenericDeck_maskToString(&CurDeck, ((void *) &(m)), (s))

/* As an alternative to the CurDeck approach, provide another set of macros
   that accept an object of type Deck as an argument. */
#define DcardToString(d, c, s) ((d).cardToString((c), (s)))
#define DstringToCard(d, s, i) ((d).stringToCard((s), (i)))
#define DcardString(d, i) (GenericDeck_cardString(&(d), (i)))
#define DprintCard(d, i) (GenericDeck_printCard(&(d), (i)))
#define DprintMask(d, m) (GenericDeck_printMask(&(d), ((void *) &(m))))
#define DmaskString(d, m) (GenericDeck_maskString(&(d), ((void *) &(m))))
#define DnumCards(d, m) (GenericDeck_numCards(&(d), ((void *) &(m))))
#define DmaskToString(d, m, s) (GenericDeck_maskString(&(d), ((void *) &(m)), (s)))

extern POKEREVAL_EXPORT char *
GenericDeck_cardString(Deck *deck, int cardIndex);
extern POKEREVAL_EXPORT int 
GenericDeck_printMask(Deck *deck, void *cardMask);
extern POKEREVAL_EXPORT int
GenericDeck_maskToString(Deck *deck, void *cardMask, char *outString);
extern POKEREVAL_EXPORT char *
GenericDeck_maskString(Deck *deck, void *cardMask);
extern POKEREVAL_EXPORT int
GenericDeck_printCard(Deck *deck, int cardIndex);
extern POKEREVAL_EXPORT int
GenericDeck_numCards(Deck *deck, void *cardMask);

/* These are required by the ENUMERATE_ macros */

#define Deck_CardMask              CardMask
#define Deck_CardMask_OR           CardMask_OR
#define Deck_CardMask_XOR          CardMask_XOR
#define Deck_CardMask_AND          CardMask_AND
#define Deck_CardMask_RESET        CardMask_RESET
#define Deck_CardMask_ANY_SET      CardMask_ANY_SET
#define Deck_CardMask_CARD_IS_SET  CardMask_CARD_IS_SET

/* include/handval.h */
typedef uint32 HandVal;

#define HandVal_HANDTYPE_SHIFT    24
#define HandVal_HANDTYPE_MASK     0x0F000000
#define HandVal_CARDS_SHIFT       0
#define HandVal_CARDS_MASK        0x000FFFFF
#define HandVal_TOP_CARD_SHIFT    16
#define HandVal_TOP_CARD_MASK     0x000F0000
#define HandVal_SECOND_CARD_SHIFT 12
#define HandVal_SECOND_CARD_MASK  0x0000F000
#define HandVal_THIRD_CARD_SHIFT  8
#define HandVal_THIRD_CARD_MASK   0x00000F00
#define HandVal_FOURTH_CARD_SHIFT 4
#define HandVal_FOURTH_CARD_MASK  0x000000F0
#define HandVal_FIFTH_CARD_SHIFT  0
#define HandVal_FIFTH_CARD_MASK   0x0000000F
#define HandVal_CARD_WIDTH        4
#define HandVal_CARD_MASK         0x0F

#define HandVal_HANDTYPE(hv)   ((hv) >> HandVal_HANDTYPE_SHIFT)
#define HandVal_CARDS(hv)      ((hv) & HandVal_CARDS_MASK)
#define HandVal_TOP_CARD(hv) \
  (((hv) >> HandVal_TOP_CARD_SHIFT) & HandVal_CARD_MASK)
#define HandVal_SECOND_CARD(hv) \
  (((hv) >> HandVal_SECOND_CARD_SHIFT) & HandVal_CARD_MASK)
#define HandVal_THIRD_CARD(hv) \
  (((hv) >> HandVal_THIRD_CARD_SHIFT) & HandVal_CARD_MASK)
#define HandVal_FOURTH_CARD(hv) \
  (((hv) >> HandVal_FOURTH_CARD_SHIFT) & HandVal_CARD_MASK)
#define HandVal_FIFTH_CARD(hv) \
  (((hv) >> HandVal_FIFTH_CARD_SHIFT) & HandVal_CARD_MASK)

#define HandVal_HANDTYPE_VALUE(ht)   ((ht) << HandVal_HANDTYPE_SHIFT)
#define HandVal_TOP_CARD_VALUE(c)    ((c) << HandVal_TOP_CARD_SHIFT)
#define HandVal_SECOND_CARD_VALUE(c) ((c) << HandVal_SECOND_CARD_SHIFT)
#define HandVal_THIRD_CARD_VALUE(c)  ((c) << HandVal_THIRD_CARD_SHIFT)
#define HandVal_FOURTH_CARD_VALUE(c) ((c) << HandVal_FOURTH_CARD_SHIFT)
#define HandVal_FIFTH_CARD_VALUE(c)  ((c) << HandVal_FIFTH_CARD_SHIFT)

#define HandVal_NOTHING 0

/* include/handval_low.h */
typedef uint32 LowHandVal;

#define LowHandVal_HANDTYPE_SHIFT    HandVal_HANDTYPE_SHIFT    
#define LowHandVal_HANDTYPE_MASK     HandVal_HANDTYPE_MASK     
#define LowHandVal_CARDS_SHIFT       HandVal_CARDS_SHIFT       
#define LowHandVal_CARDS_MASK        HandVal_CARDS_MASK        
#define LowHandVal_TOP_CARD_SHIFT    HandVal_TOP_CARD_SHIFT    
#define LowHandVal_TOP_CARD_MASK     HandVal_TOP_CARD_MASK     
#define LowHandVal_SECOND_CARD_SHIFT HandVal_SECOND_CARD_SHIFT 
#define LowHandVal_SECOND_CARD_MASK  HandVal_SECOND_CARD_MASK  
#define LowHandVal_THIRD_CARD_SHIFT  HandVal_THIRD_CARD_SHIFT  
#define LowHandVal_THIRD_CARD_MASK   HandVal_THIRD_CARD_MASK   
#define LowHandVal_FOURTH_CARD_SHIFT HandVal_FOURTH_CARD_SHIFT 
#define LowHandVal_FOURTH_CARD_MASK  HandVal_FOURTH_CARD_MASK  
#define LowHandVal_FIFTH_CARD_SHIFT  HandVal_FIFTH_CARD_SHIFT  
#define LowHandVal_FIFTH_CARD_MASK   HandVal_FIFTH_CARD_MASK   
#define LowHandVal_CARD_WIDTH        HandVal_CARD_WIDTH        
#define LowHandVal_CARD_MASK         HandVal_CARD_MASK         

#define LowHandVal_HANDTYPE          HandVal_HANDTYPE
#define LowHandVal_CARDS             HandVal_CARDS
#define LowHandVal_TOP_CARD          HandVal_TOP_CARD
#define LowHandVal_SECOND_CARD       HandVal_SECOND_CARD
#define LowHandVal_THIRD_CARD        HandVal_THIRD_CARD
#define LowHandVal_FOURTH_CARD       HandVal_FOURTH_CARD
#define LowHandVal_FIFTH_CARD        HandVal_FIFTH_CARD

#define LowHandVal_HANDTYPE_VALUE    HandVal_HANDTYPE_VALUE
#define LowHandVal_TOP_CARD_VALUE    HandVal_TOP_CARD_VALUE
#define LowHandVal_SECOND_CARD_VALUE HandVal_SECOND_CARD_VALUE
#define LowHandVal_THIRD_CARD_VALUE  HandVal_THIRD_CARD_VALUE
#define LowHandVal_FOURTH_CARD_VALUE HandVal_FOURTH_CARD_VALUE
#define LowHandVal_FIFTH_CARD_VALUE  HandVal_FIFTH_CARD_VALUE

#define LowHandVal_NOTHING                              \
(LowHandVal_HANDTYPE_VALUE(StdRules_HandType_STFLUSH)   \
 + LowHandVal_TOP_CARD_VALUE(StdDeck_Rank_ACE) + 1)

#define LowHandVal_WORST_EIGHT \
(LowHandVal_HANDTYPE_VALUE(StdRules_HandType_NOPAIR)     \
 + LowHandVal_TOP_CARD_VALUE(StdDeck_Rank_8+1)           \
 + LowHandVal_SECOND_CARD_VALUE(StdDeck_Rank_7+1)        \
 + LowHandVal_THIRD_CARD_VALUE(StdDeck_Rank_6+1)         \
 + LowHandVal_FOURTH_CARD_VALUE(StdDeck_Rank_5+1)        \
 + LowHandVal_FIFTH_CARD_VALUE(StdDeck_Rank_4+1))         

extern POKEREVAL_EXPORT int LowHandVal_toString(LowHandVal hv, char *outString);
extern POKEREVAL_EXPORT int LowHandVal_print(LowHandVal handval);

#define Lowball_ROTATE_RANKS(ranks) \
((((ranks) & ~(1 << StdDeck_Rank_ACE)) << 1) \
 | (((ranks) >> StdDeck_Rank_ACE) & 0x01))

#define Lowball_JOKERFY_RANKS(ranks)		\
do { int j;					\
  for (j=0; j < StdDeck_Rank_COUNT; j++)	\
    if (!(ranks) & (1 << j))			\
      (ranks) |= (1 << j);			\
} while (0)

/* include/enumerate.h */
/*
Macros to enumerate combinations and permutations of the remaining
cards in a deck.  Each macro accepts an argument containing code that
is executed in the inner loop of the enumeration.

------------------------------------------------------------------------
DECK_ENUMERATE_x_CARDS(deck, cards_var, action)
Visits every x-card subset of deck 'deck'.  For each subset, sets 'cards'
to the cards in the subset and invokes the code in 'var_action'.
	x = {1..7} 
        deck -- type Deck, one of {StdDeck, JokerDeck, AStudDeck}
        cards_var -- type deck##_CardMask, for use in action code, contains
        	     the current subset of cards, declared by caller
        action -- C code to run in macro inner loop


------------------------------------------------------------------------
DECK_ENUMERATE_x_CARDS_D(deck, cards_var, dead_cards, action)
Similar to DECK_ENUMERATE_x_CARDS(), but cards in 'dead_cards' are not
included in any subset.
  	dead_cards -- type deck##_CardMask, the set of cards not to deal


------------------------------------------------------------------------
DECK_MONTECARLO_N_CARDS_D(deck, cards_var, dead_cards,
                          num_cards, num_iter, action)
Similar to DECK_ENUMERATE_x_CARDS(), but instead of exhaustively enumerating
all possible subsets, this macro randomly samples the subsets (with
replacement).
	num_cards -- type int, the number of cards to store in cards_var
	num_iter -- type int, the number of samples to draw

------------------------------------------------------------------------
DECK_ENUMERATE_COMBINATIONS_D(deck, set_var, num_sets, set_sizes, 
                              dead_cards, action).
Visits every ordered set of set_sizes[i]-sized card unordered subsets of deck
'deck'.  This is intended for games such as stud or draw, where each player
will receive his own cards, and the number of received cards may differ among
players.
        set_var -- type deck##_CardMask[], for use in action code, gives 
                   the set of cards dealt to each player in this iteration,
                   declared by caller
        num_sets -- type int, dimension of set_sizes array (number of players)
        set_sizes -- type int[], number of cards to be received by each player
        dead_cards -- type deck##_CardMask, the set of cards not to deal
        action -- C code to run in macro inner loop

------------------------------------------------------------------------
DECK_ENUMERATE_PERMUTATIONS_D(deck, set_var, num_sets, set_sizes, 
                              dead_cards, action).
Visits every ordered set of set_sizes[i]-sized card ordered subsets of deck
'deck'.  This is intended for games in which each player receives his own
cards and the order of received cards is important.
        set_var -- type deck##_CardMask[], for use in action code, gives 
                   the set of cards dealt to each player in this iteration,
                   declared by caller
        num_sets -- type int, dimension of set_sizes array (number of players)
        set_sizes -- type int[], number of cards to be received by each player
        dead_cards -- type deck##_CardMask, the set of cards not to deal
        action -- C code to run in macro inner loop

------------------------------------------------------------------------
DECK_MONTECARLO_PERMUTATIONS_D(deck, set_var, num_sets, set_sizes, 
                               dead_cards, num_iter, action)
Like DECK_ENUMERATE_PERMUTATIONS_D(), but but instead of exhaustively
enumerating all possible ordered sets of subsets, this macro randomly samples
them (with replacement).
	num_iter -- type int, the number of samples to draw */

#ifndef RANDOM
#define RANDOM rand
#endif

#define DECK_ENUMERATE_1_CARDS(deck, cards_var, action) \
do {                                                    \
  int _i1;                                              \
  deck##_CardMask _card;                                \
                                                        \
  for (_i1 = deck##_N_CARDS-1; _i1 >= 0; _i1--) {       \
    _card = deck##_MASK(_i1);                           \
    cards_var = _card;                                  \
    { action };                                         \
  };                                                    \
} while (0)

#define DECK_ENUMERATE_2_CARDS(deck, cards_var, action) \
do {                                                    \
  int _i1, _i2;                                         \
  deck##_CardMask _card1, _card2,                       \
    _n2;                                                \
                                                        \
  for (_i1 = deck##_N_CARDS-1; _i1 >= 0; _i1--) {       \
    _card1 = deck##_MASK(_i1);                          \
    for (_i2 = _i1-1; _i2 >= 0; _i2--) {                \
      _card2 = deck##_MASK(_i2);                        \
      deck##_CardMask_OR(_n2, _card1, _card2);          \
      cards_var = _n2;                                  \
      { action };                                       \
    };                                                  \
  };                                                    \
} while (0)

#define DECK_ENUMERATE_3_CARDS(deck, cards_var, action) \
do {                                                    \
  int _i1, _i2, _i3;                                    \
  deck##_CardMask _card1, _card2, _card3,               \
    _n2, _n3;                                           \
                                                        \
  for (_i1 = deck##_N_CARDS-1; _i1 >= 0; _i1--) {       \
    _card1 = deck##_MASK(_i1);                          \
    for (_i2 = _i1-1; _i2 >= 0; _i2--) {                \
      _card2 = deck##_MASK(_i2);                        \
      deck##_CardMask_OR(_n2, _card1, _card2);          \
      for (_i3 = _i2-1; _i3 >= 0; _i3--) {              \
        _card3 = deck##_MASK(_i3);                      \
	deck##_CardMask_OR(_n3, _n2, _card3);           \
        cards_var = _n3;                                \
        { action };                                     \
      };                                                \
    };                                                  \
  };                                                    \
} while (0)

#define DECK_ENUMERATE_4_CARDS(deck, cards_var, action) \
do {                                                    \
  int _i1, _i2, _i3, _i4;                               \
  deck##_CardMask _card1, _card2, _card3, _card4,       \
    _n2, _n3, _n4;                                      \
                                                        \
  for (_i1 = deck##_N_CARDS-1; _i1 >= 0; _i1--) {       \
    _card1 = deck##_MASK(_i1);                          \
    for (_i2 = _i1-1; _i2 >= 0; _i2--) {                \
      _card2 = deck##_MASK(_i2);                        \
      deck##_CardMask_OR(_n2, _card1, _card2);          \
      for (_i3 = _i2-1; _i3 >= 0; _i3--) {              \
        _card3 = deck##_MASK(_i3);                      \
	deck##_CardMask_OR(_n3, _n2, _card3);           \
        for (_i4 = _i3-1; _i4 >= 0; _i4--) {            \
          _card4 = deck##_MASK(_i4);                    \
	  deck##_CardMask_OR(_n4, _n3, _card4);         \
          cards_var = _n4;                              \
          { action };                                   \
        };                                              \
      };                                                \
    };                                                  \
  };                                                    \
} while (0)

#define DECK_ENUMERATE_5_CARDS(deck, cards_var, action)                   \
do {                                                                      \
  int _i1, _i2, _i3, _i4, _i5;                                            \
  deck##_CardMask _card1, _card2, _card3, _card4, _card5,                 \
    _n2, _n3, _n4, _n5;                                                   \
                                                                          \
  for (_i1 = deck##_N_CARDS-1; _i1 >= 0; _i1--) {                         \
    _card1 = deck##_MASK(_i1);                                            \
    for (_i2 = _i1-1; _i2 >= 0; _i2--) {                                  \
      _card2 = deck##_MASK(_i2);                                          \
      deck##_CardMask_OR(_n2, _card1, _card2);                            \
      for (_i3 = _i2-1; _i3 >= 0; _i3--) {                                \
        _card3 = deck##_MASK(_i3);                                        \
	deck##_CardMask_OR(_n3, _n2, _card3);                             \
        for (_i4 = _i3-1; _i4 >= 0; _i4--) {                              \
          _card4 = deck##_MASK(_i4);                                      \
	  deck##_CardMask_OR(_n4, _n3, _card4);                           \
          for (_i5 = _i4-1; _i5 >= 0; _i5--) {                            \
            _card5 = deck##_MASK(_i5);                                    \
            deck##_CardMask_OR(_n5, _n4, _card5);                         \
            cards_var = _n5;                                              \
            { action };                                                   \
          };                                                              \
        };                                                                \
      };                                                                  \
    };                                                                    \
  };                                                                      \
} while (0)                                                               
                                                                          
#define DECK_ENUMERATE_7_CARDS(deck, cards_var, action)                   \
do {                                                                      \
  int _i1, _i2, _i3, _i4, _i5, _i6, _i7;                                  \
  deck##_CardMask _card1, _card2, _card3, _card4, _card5, _card6, _card7, \
    _n2, _n3, _n4, _n5, _n6, _n7;                                         \
                                                                          \
  for (_i1 = deck##_N_CARDS-1; _i1 >= 0; _i1--) {                         \
    _card1 = deck##_MASK(_i1);                                            \
    for (_i2 = _i1-1; _i2 >= 0; _i2--) {                                  \
      _card2 = deck##_MASK(_i2);                                          \
      deck##_CardMask_OR(_n2, _card1, _card2);                            \
      for (_i3 = _i2-1; _i3 >= 0; _i3--) {                                \
        _card3 = deck##_MASK(_i3);                                        \
	deck##_CardMask_OR(_n3, _n2, _card3);                             \
        for (_i4 = _i3-1; _i4 >= 0; _i4--) {                              \
          _card4 = deck##_MASK(_i4);                                      \
	  deck##_CardMask_OR(_n4, _n3, _card4);                           \
          for (_i5 = _i4-1; _i5 >= 0; _i5--) {                            \
            _card5 = deck##_MASK(_i5);                                    \
            deck##_CardMask_OR(_n5, _n4, _card5);                         \
            for (_i6 = _i5-1; _i6 >= 0; _i6--) {                          \
              _card6 = deck##_MASK(_i6);                                  \
              deck##_CardMask_OR(_n6, _n5, _card6);                       \
              for (_i7 = _i6-1; _i7 >= 0; _i7--) {                        \
                _card7 = deck##_MASK(_i7);                                \
                deck##_CardMask_OR(_n7, _n6, _card7);                     \
                cards_var = _n7;                                          \
                { action };                                               \
              };                                                          \
            };                                                            \
          };                                                              \
        };                                                                \
      };                                                                  \
    };                                                                    \
  };                                                                      \
} while (0)


#define DECK_ENUMERATE_1_CARDS_D(deck, cards_var, dead_cards, action)   \
do {                                                                    \
  int _i1;                                                              \
  deck##_CardMask _card;                                                \
                                                                        \
  for (_i1 = deck##_N_CARDS-1; _i1 >= 0; _i1--) {                       \
    _card = deck##_MASK(_i1);                                           \
    if (deck##_CardMask_ANY_SET(dead_cards, _card))                     \
      continue;                                                         \
    cards_var = _card;                                                  \
    { action };                                                         \
  };                                                                    \
} while (0)

#define DECK_ENUMERATE_2_CARDS_D(deck, cards_var, dead_cards, action)   \
do {                                                                    \
  int _i1; int _i2;							\
  deck##_CardMask _card1; deck##_CardMask _card2;			\
  deck##_CardMask _n2;							\
                                                                        \
  for (_i1 = deck##_N_CARDS-1; _i1 >= 0; _i1--) {                       \
    _card1 = deck##_MASK(_i1);                                          \
    if (deck##_CardMask_ANY_SET(dead_cards, _card1))                    \
      continue;                                                         \
    for (_i2 = _i1-1; _i2 >= 0; _i2--) {                                \
      _card2 = deck##_MASK(_i2);                                        \
      if (deck##_CardMask_ANY_SET(dead_cards, _card2))                  \
        continue;                                                       \
      deck##_CardMask_OR(_n2, _card1, _card2);                          \
      cards_var = _n2;                                                  \
      { action };                                                       \
    };                                                                  \
  };                                                                    \
} while (0)                                                             
                                                                        
#define DECK_ENUMERATE_3_CARDS_D(deck, cards_var, dead_cards, action)   \
do {                                                                    \
  int _i1, _i2, _i3;                                                    \
  deck##_CardMask _card1, _card2, _card3,                               \
    _n2, _n3;                                                           \
                                                                        \
  for (_i1 = deck##_N_CARDS-1; _i1 >= 0; _i1--) {                       \
    _card1 = deck##_MASK(_i1);                                          \
    if (deck##_CardMask_ANY_SET(dead_cards, _card1))                    \
      continue;                                                         \
    for (_i2 = _i1-1; _i2 >= 0; _i2--) {                                \
      _card2 = deck##_MASK(_i2);                                        \
      if (deck##_CardMask_ANY_SET(dead_cards, _card2))                  \
        continue;                                                       \
      deck##_CardMask_OR(_n2, _card1, _card2);                          \
      for (_i3 = _i2-1; _i3 >= 0; _i3--) {                              \
        _card3 = deck##_MASK(_i3);                                      \
        if (deck##_CardMask_ANY_SET(dead_cards, _card3))                \
          continue;                                                     \
	deck##_CardMask_OR(_n3, _n2, _card3);                           \
        cards_var = _n3;                                                \
        { action };                                                     \
      };                                                                \
    };                                                                  \
  };                                                                    \
} while (0)                                                             
                                                                        
#define DECK_ENUMERATE_4_CARDS_D(deck, cards_var, dead_cards, action)   \
do {                                                                    \
  int _i1, _i2, _i3, _i4;                                               \
  deck##_CardMask _card1, _card2, _card3, _card4,                       \
    _n2, _n3, _n4;                                                      \
                                                                        \
  for (_i1 = deck##_N_CARDS-1; _i1 >= 0; _i1--) {                       \
    _card1 = deck##_MASK(_i1);                                          \
    if (deck##_CardMask_ANY_SET(dead_cards, _card1))                    \
      continue;                                                         \
    for (_i2 = _i1-1; _i2 >= 0; _i2--) {                                \
      _card2 = deck##_MASK(_i2);                                        \
      if (deck##_CardMask_ANY_SET(dead_cards, _card2))                  \
        continue;                                                       \
      deck##_CardMask_OR(_n2, _card1, _card2);                          \
      for (_i3 = _i2-1; _i3 >= 0; _i3--) {                              \
        _card3 = deck##_MASK(_i3);                                      \
        if (deck##_CardMask_ANY_SET(dead_cards, _card3))                \
          continue;                                                     \
	deck##_CardMask_OR(_n3, _n2, _card3);                           \
        for (_i4 = _i3-1; _i4 >= 0; _i4--) {                            \
          _card4 = deck##_MASK(_i4);                                    \
          if (deck##_CardMask_ANY_SET(dead_cards, _card4))              \
            continue;                                                   \
	  deck##_CardMask_OR(_n4, _n3, _card4);                         \
          cards_var = _n4;                                              \
          { action };                                                   \
        };                                                              \
      };                                                                \
    };                                                                  \
  };                                                                    \
} while (0)                                                             
                                                                        
#define DECK_ENUMERATE_5_CARDS_D(deck, cards_var, dead_cards, action)   \
do {                                                                    \
  int _i1, _i2, _i3, _i4, _i5;                                          \
  deck##_CardMask _card1, _card2, _card3, _card4, _card5,               \
    _n2, _n3, _n4, _n5;                                                 \
                                                                        \
  for (_i1 = deck##_N_CARDS-1; _i1 >= 0; _i1--) {                       \
    _card1 = deck##_MASK(_i1);                                          \
    if (deck##_CardMask_ANY_SET(dead_cards, _card1))                    \
      continue;                                                         \
    for (_i2 = _i1-1; _i2 >= 0; _i2--) {                                \
      _card2 = deck##_MASK(_i2);                                        \
      if (deck##_CardMask_ANY_SET(dead_cards, _card2))                  \
        continue;                                                       \
      deck##_CardMask_OR(_n2, _card1, _card2);                          \
      for (_i3 = _i2-1; _i3 >= 0; _i3--) {                              \
        _card3 = deck##_MASK(_i3);                                      \
        if (deck##_CardMask_ANY_SET(dead_cards, _card3))                \
          continue;                                                     \
	deck##_CardMask_OR(_n3, _n2, _card3);                           \
        for (_i4 = _i3-1; _i4 >= 0; _i4--) {                            \
          _card4 = deck##_MASK(_i4);                                    \
          if (deck##_CardMask_ANY_SET(dead_cards, _card4))              \
            continue;                                                   \
	  deck##_CardMask_OR(_n4, _n3, _card4);                         \
          for (_i5 = _i4-1; _i5 >= 0; _i5--) {                          \
            _card5 = deck##_MASK(_i5);                                  \
            if (deck##_CardMask_ANY_SET(dead_cards, _card5))            \
              continue;                                                 \
            deck##_CardMask_OR(_n5, _n4, _card5);                       \
            cards_var = _n5;                                            \
            { action };                                                 \
          };                                                            \
        };                                                              \
      };                                                                \
    };                                                                  \
  };                                                                    \
} while (0)




#define DECK_ENUMERATE_N_CARDS_D(deck, cards_var, n_cards, dead_cards,     \
                                 action)                                   \
do {                                                                       \
  int _i1; int _i2; int _i3;						\
  int _i4; int _i5; int _i6;						\
  int _i7; int _i8; int _i9;						\
  deck##_CardMask _card1; deck##_CardMask _card2; deck##_CardMask _card3; \
  deck##_CardMask _card4; deck##_CardMask _card5; deck##_CardMask _card6; \
  deck##_CardMask _card7; deck##_CardMask _card8; deck##_CardMask _card9; \
  deck##_CardMask _n1; deck##_CardMask _n2; deck##_CardMask _n3;	\
  deck##_CardMask _n4; deck##_CardMask _n5; deck##_CardMask _n6;	\
  deck##_CardMask _n7; deck##_CardMask _n8; deck##_CardMask _n9;	\
                                                                           \
  _i1 = _i2 = _i3 = _i4 = _i5 = _i6 = _i7 = _i8 = _i9 = 0;                 \
  deck##_CardMask_RESET(_card9);                                           \
  _card1 = _card2 = _card3 = _card4 = _card5 = _card6                      \
    = _card7 = _card8 = _card9;                                            \
  deck##_CardMask_RESET(_n9);                                              \
  _n1 = _n2 = _n3 = _n4 = _n5 = _n6 = _n7 = _n8 = _n9;                     \
                                                                           \
  switch (n_cards) {                                                       \
  default:                                                                 \
  case 9:                                                                  \
  case 0:                                                                  \
    break;                                                                 \
  case 8:                                                                  \
    _i2 = deck##_N_CARDS-1;                                                \
    break;                                                                 \
  case 7:                                                                  \
    _i3 = deck##_N_CARDS-1;                                                \
    break;                                                                 \
  case 6:                                                                  \
    _i4 = deck##_N_CARDS-1;                                                \
    break;                                                                 \
  case 5:                                                                  \
    _i5 = deck##_N_CARDS-1;                                                \
    break;                                                                 \
  case 4:                                                                  \
    _i6 = deck##_N_CARDS-1;                                                \
    break;                                                                 \
  case 3:                                                                  \
    _i7 = deck##_N_CARDS-1;                                                \
    break;                                                                 \
  case 2:                                                                  \
    _i8 = deck##_N_CARDS-1;                                                \
    break;                                                                 \
  case 1:                                                                  \
    _i9 = deck##_N_CARDS-1;                                                \
    break;                                                                 \
  }                                                                        \
  switch (n_cards) {                                                       \
  default:                                                                 \
    fprintf(stderr, "ENUMERATE_N_CARDS: n-cards must be in range 0..9\n"); \
    break;                                                                 \
                                                                           \
  case 9:                                                                  \
    for (_i1 = deck##_N_CARDS-1; _i1 >= 0; _i1--) {                        \
      _card1 = deck##_MASK(_i1);                                           \
      if (deck##_CardMask_ANY_SET(dead_cards, _card1))                     \
        continue;                                                          \
      _n1 = _card1;                                                        \
      for (_i2 = _i1-1; _i2 >= 0; _i2--) {                                 \
  case 8:                                                                  \
        _card2 = deck##_MASK(_i2);                                         \
        if (deck##_CardMask_ANY_SET(dead_cards, _card2))                   \
          continue;                                                        \
        deck##_CardMask_OR(_n2, _n1, _card2);                              \
        for (_i3 = _i2-1; _i3 >= 0; _i3--) {                               \
  case 7:                                                                  \
          _card3 = deck##_MASK(_i3);                                       \
          if (deck##_CardMask_ANY_SET(dead_cards, _card3))                 \
            continue;                                                      \
          deck##_CardMask_OR(_n3, _n2, _card3);                            \
          for (_i4 = _i3-1; _i4 >= 0; _i4--) {                             \
  case 6:                                                                  \
            _card4 = deck##_MASK(_i4);                                     \
            if (deck##_CardMask_ANY_SET(dead_cards, _card4))               \
              continue;                                                    \
            deck##_CardMask_OR(_n4, _n3, _card4);                          \
            for (_i5 = _i4-1; _i5 >= 0; _i5--) {                           \
  case 5:                                                                  \
              _card5 = deck##_MASK(_i5);                                   \
              if (deck##_CardMask_ANY_SET(dead_cards, _card5))             \
                continue;                                                  \
              deck##_CardMask_OR(_n5, _n4, _card5);                        \
              for (_i6 = _i5-1; _i6 >= 0; _i6--) {                         \
  case 4:                                                                  \
                _card6 = deck##_MASK(_i6);                                 \
                if (deck##_CardMask_ANY_SET(dead_cards, _card6))           \
                  continue;                                                \
                deck##_CardMask_OR(_n6, _n5, _card6);                      \
                for (_i7 = _i6-1; _i7 >= 0; _i7--) {                       \
  case 3:                                                                  \
                  _card7 = deck##_MASK(_i7);                               \
                  if (deck##_CardMask_ANY_SET(dead_cards, _card7))         \
                    continue;                                              \
                  deck##_CardMask_OR(_n7, _n6, _card7);                    \
                  for (_i8 = _i7-1; _i8 >= 0; _i8--) {                     \
  case 2:                                                                  \
                    _card8 = deck##_MASK(_i8);                             \
                    if (deck##_CardMask_ANY_SET(dead_cards, _card8))       \
                      continue;                                            \
                    deck##_CardMask_OR(_n8, _n7, _card8);                  \
                    for (_i9 = _i8-1; _i9 >= 0; _i9--) {                   \
  case 1:                                                                  \
                      _card9 = deck##_MASK(_i9);                           \
                      if (deck##_CardMask_ANY_SET(dead_cards, _card9))     \
                        continue;                                          \
                      deck##_CardMask_OR(_n9, _n8, _card9);                \
  case 0:                                                                  \
                        cards_var = _n9;                                   \
                        { action };                                        \
		    }                                                      \
		  }                                                        \
		}                                                          \
	      }                                                            \
	    }                                                              \
	  }                                                                \
	}                                                                  \
      }                                                                    \
    }                                                                      \
  }                                                                        \
} while (0)                                                                
                                                                           
                                                                           
#define DECK_ENUMERATE_N_CARDS(deck, cards_var, n_cards, action)           \
do {                                                                       \
  int _i1, _i2, _i3, _i4, _i5, _i6, _i7, _i8, _i9;                         \
  deck##_CardMask _card1, _card2, _card3, _card4, _card5,                  \
    _card6, _card7, _card8, _card9,                                        \
    _n1, _n2, _n3, _n4, _n5, _n6, _n7, _n8, _n9;                           \
                                                                           \
  _i1 = _i2 = _i3 = _i4 = _i5 = _i6 = _i7 = _i8 = _i9 = 0;                 \
  deck##_CardMask_RESET(_card9);                                           \
  _card1 = _card2 = _card3 = _card4 = _card5 = _card6                      \
    = _card7 = _card8 = _card9;                                            \
  deck##_CardMask_RESET(_n9);                                              \
  _n1 = _n2 = _n3 = _n4 = _n5 = _n6 = _n7 = _n8 = _n9;                     \
                                                                           \
  switch (n_cards) {                                                       \
  default:                                                                 \
  case 9:                                                                  \
  case 0:                                                                  \
    break;                                                                 \
  case 8:                                                                  \
    _i2 = deck##_N_CARDS-1;                                                \
    break;                                                                 \
  case 7:                                                                  \
    _i3 = deck##_N_CARDS-1;                                                \
    break;                                                                 \
  case 6:                                                                  \
    _i4 = deck##_N_CARDS-1;                                                \
    break;                                                                 \
  case 5:                                                                  \
    _i5 = deck##_N_CARDS-1;                                                \
    break;                                                                 \
  case 4:                                                                  \
    _i6 = deck##_N_CARDS-1;                                                \
    break;                                                                 \
  case 3:                                                                  \
    _i7 = deck##_N_CARDS-1;                                                \
    break;                                                                 \
  case 2:                                                                  \
    _i8 = deck##_N_CARDS-1;                                                \
    break;                                                                 \
  case 1:                                                                  \
    _i9 = deck##_N_CARDS-1;                                                \
    break;                                                                 \
  }                                                                        \
  switch (n_cards) {                                                       \
  default:                                                                 \
    fprintf(stderr, "ENUMERATE_N_CARDS: n-cards must be in range 0..9\n"); \
    break;                                                                 \
                                                                           \
  case 9:                                                                  \
    for (_i1 = deck##_N_CARDS-1; _i1 >= 0; _i1--) {                        \
      _card1 = deck##_MASK(_i1);                                           \
      _n1 = _card1;                                                        \
      for (_i2 = _i1-1; _i2 >= 0; _i2--) {                                 \
  case 8:                                                                  \
        _card2 = deck##_MASK(_i2);                                         \
        deck##_CardMask_OR(_n2, _n1, _card2);                              \
        for (_i3 = _i2-1; _i3 >= 0; _i3--) {                               \
  case 7:                                                                  \
          _card3 = deck##_MASK(_i3);                                       \
          deck##_CardMask_OR(_n3, _n2, _card3);                            \
          for (_i4 = _i3-1; _i4 >= 0; _i4--) {                             \
  case 6:                                                                  \
            _card4 = deck##_MASK(_i4);                                     \
            deck##_CardMask_OR(_n4, _n3, _card4);                          \
            for (_i5 = _i4-1; _i5 >= 0; _i5--) {                           \
  case 5:                                                                  \
              _card5 = deck##_MASK(_i5);                                   \
              deck##_CardMask_OR(_n5, _n4, _card5);                        \
              for (_i6 = _i5-1; _i6 >= 0; _i6--) {                         \
  case 4:                                                                  \
                _card6 = deck##_MASK(_i6);                                 \
                deck##_CardMask_OR(_n6, _n5, _card6);                      \
                for (_i7 = _i6-1; _i7 >= 0; _i7--) {                       \
  case 3:                                                                  \
                  _card7 = deck##_MASK(_i7);                               \
                  deck##_CardMask_OR(_n7, _n6, _card7);                    \
                  for (_i8 = _i7-1; _i8 >= 0; _i8--) {                     \
  case 2:                                                                  \
                    _card8 = deck##_MASK(_i8);                             \
                    deck##_CardMask_OR(_n8, _n7, _card8);                  \
                    for (_i9 = _i8-1; _i9 >= 0; _i9--) {                   \
  case 1:                                                                  \
                      _card9 = deck##_MASK(_i9);                           \
                      deck##_CardMask_OR(_n9, _n8, _card9);                \
  case 0:                                                                  \
                        cards_var = _n9;                                   \
                        { action };                                        \
		    }                                                      \
		  }                                                        \
		}                                                          \
	      }                                                            \
	    }                                                              \
	  }                                                                \
	}                                                                  \
      }                                                                    \
    }                                                                      \
  }                                                                        \
} while (0)

typedef void *Combinations;

extern POKEREVAL_EXPORT void free_combinations(Combinations c);
extern POKEREVAL_EXPORT Combinations init_combinations(int nuniv, int nelem);
extern POKEREVAL_EXPORT int num_combinations(Combinations c);
extern POKEREVAL_EXPORT void get_combination(Combinations c, int cnum, int *elems);


#define DECK_ENUMERATE_COMBINATIONS_D(deck, set_var, num_sets, set_sizes, \
                                      dead_cards, action) \
do { \
  Combinations *_combos; \
  int *_ncombo; \
  int *_curIndex; \
  int **_curElem; \
  deck##_CardMask *_curHand; \
  deck##_CardMask _avail; \
  deck##_CardMask _unavail; \
  int _lowestRoll; \
  int _couldIncr; \
  int _i, _j, _k; \
   \
  _combos = (Combinations *) malloc(num_sets * sizeof(Combinations)); \
  _ncombo = (int *) malloc(num_sets * sizeof(int)); \
  _curIndex = (int *) malloc(num_sets * sizeof(int)); \
  _curElem = (int **) malloc(num_sets * sizeof(intptr_t)); \
  _curHand = (deck##_CardMask *) malloc(num_sets * sizeof(deck##_CardMask)); \
  for (_i=0; _i<num_sets; _i++) { \
    _combos[_i] = init_combinations(deck##_N_CARDS, set_sizes[_i]); \
    _ncombo[_i] = num_combinations(_combos[_i]); \
    _curElem[_i] = (int *) malloc(set_sizes[_i] * sizeof(int)); \
  } \
  _unavail = dead_cards; \
  _lowestRoll = 0; \
  do { \
    /* for each player rolling over, find the lowest available hand */ \
    for (_i=_lowestRoll; _i<num_sets; _i++) { \
      /* for each candidate hand for player i */ \
      for (_j=0; _j<_ncombo[_i]; _j++) { \
        get_combination(_combos[_i], _j, _curElem[_i]); \
        deck##_CardMask_RESET(set_var[_i]); \
        for (_k=0; _k<set_sizes[_i]; _k++) \
          deck##_CardMask_SET(set_var[_i], _curElem[_i][_k]); \
        if (!deck##_CardMask_ANY_SET(_unavail, set_var[_i])) \
          break;	/* this hand is available for player i */ \
      } \
      if (_j == _ncombo[_i]) { printf("not enough cards\n"); return(1); } \
      deck##_CardMask_OR(_unavail, _unavail, set_var[_i]); \
      _curIndex[_i] = _j; \
    } \
 \
    { action } \
 \
    /* Now increment the least significant player's hand, and if it overflows, \
       carry into the next player's hand.  Set lowestRoll to the most \
       significant player whose hand overflowed. */ \
    _couldIncr = 0; \
    for (_i=num_sets-1; _i>=0; _i--) { \
      deck##_CardMask_NOT(_avail, set_var[_i]); \
      deck##_CardMask_AND(_unavail, _unavail, _avail); \
      for (_j=_curIndex[_i]+1; _j<_ncombo[_i]; _j++) { \
        get_combination(_combos[_i], _j, _curElem[_i]); \
        deck##_CardMask_RESET(set_var[_i]); \
        for (_k=0; _k<set_sizes[_i]; _k++) \
          deck##_CardMask_SET(set_var[_i], _curElem[_i][_k]); \
        if (!deck##_CardMask_ANY_SET(_unavail, set_var[_i])) \
          break;	/* this hand is available for player i */ \
      } \
      if (_j < _ncombo[_i]) { \
        deck##_CardMask_OR(_unavail, _unavail, set_var[_i]); \
        _curIndex[_i] = _j; \
        _couldIncr = 1; \
        _lowestRoll = _i + 1; \
        break; \
      } \
    } \
  } while (_couldIncr); \
  for (_i=0; _i<num_sets; _i++) { \
    free_combinations(_combos[_i]); \
    free(_curElem[_i]); \
  } \
  free(_combos); \
  free(_ncombo); \
  free(_curIndex); \
  free(_curElem); \
  free(_curHand); \
} while (0)

#define DECK_ENUMERATE_PERMUTATIONS_D(deck, set_var, num_sets, set_sizes, \
                                      dead_cards, action)                 \
do {                                                                      \
  deck##_CardMask _orMask[deck##_N_CARDS+1];                              \
  int _i, _j, _t, _index, _nLiveCards, _nCards,                           \
    _liveCards[deck##_N_CARDS], _indices[deck##_N_CARDS+1];               \
  _nCards = _nLiveCards = 0;                                              \
  for (_i=0; _i < (num_sets); _i++)                                       \
    _nCards += (set_sizes)[_i];                                           \
                                                                          \
  for (_i=0; _i < deck##_N_CARDS; _i++)                                   \
    if (!(deck##_CardMask_CARD_IS_SET(dead_cards, _i)))                   \
      _liveCards[_nLiveCards++] = _i;                                     \
                                                                          \
  if (_nLiveCards < _nCards)                                              \
    fprintf(stderr, "ENUMERATE_PERMUTATIONS: not enough cards\n");        \
  else {                                                                  \
    deck##_CardMask_RESET(_orMask[0]);                                    \
    for (_i=1; _i <= _nCards; _i++) {                                     \
      _indices[_i] = _i-1;                                                \
      deck##_CardMask_OR(_orMask[_i], _orMask[_i-1],                      \
                         deck##_MASK(_liveCards[_indices[_i]]));          \
    };                                                                    \
                                                                          \
    for (;;) {                                                            \
      set_var[0] = _orMask[set_sizes[0]];                                 \
      _t = set_sizes[0];                                                  \
      for (_j=1; _j < num_sets; _j++) {                                   \
        deck##_CardMask_XOR(set_var[_j], _orMask[_t + set_sizes[_j]],     \
                            _orMask[_t]);                                 \
        _t += set_sizes[_j];                                              \
      };                                                                  \
      { action };                                                         \
                                                                          \
      _index = _nCards;                                                   \
      do {                                                                \
        ++_indices[_index];                                               \
        while (_indices[_index] >= _nLiveCards) {                         \
          --_index;                                                       \
          if (_index == 0)                                                \
            break;                                                        \
          ++_indices[_index];                                             \
        };                                                                \
        if (_index == 0)                                                  \
          break;                                                          \
      }                                                                   \
      while (deck##_CardMask_CARD_IS_SET(_orMask[_index-1],               \
                                         _liveCards[_indices[_index]]));  \
      if (_index == 0)                                                    \
        break;                                                            \
      deck##_CardMask_OR(_orMask[_index], _orMask[_index-1],              \
                         deck##_MASK(_liveCards[_indices[_index]]));      \
      for (_i=_index+1; _i <= _nCards; _i++) {                            \
        _indices[_i] = 0;                                                 \
        while (deck##_CardMask_CARD_IS_SET(_orMask[_i-1],                 \
                                           _liveCards[_indices[_i]]))     \
          ++_indices[_i];                                                 \
        deck##_CardMask_OR(_orMask[_i], _orMask[_i-1],                    \
                           deck##_MASK(_liveCards[_indices[_i]]));        \
      };                                                                  \
    };                                                                    \
  };                                                                      \
} while (0)

#define DECK_MONTECARLO_N_CARDS_D(deck, cards_var, dead_cards,	\
                                  num_cards, num_iter, action)	\
do {                                                    	\
  int _i, _j, _c;                                              	\
  								\
  for (_i=0; _i<num_iter; _i++) {				\
    deck##_CardMask _used;					\
    _used = dead_cards;						\
    deck##_CardMask_RESET(cards_var);				\
    for (_j=0; _j<num_cards; _j++) {				\
      do {							\
        _c = RANDOM() % deck##_N_CARDS;				\
      } while (deck##_CardMask_CARD_IS_SET(_used, _c));		\
      deck##_CardMask_SET(cards_var, _c);			\
      deck##_CardMask_SET(_used, _c);				\
    }								\
    { action };                                         	\
  };                                                    	\
} while (0)

#define DECK_MONTECARLO_PERMUTATIONS_D(deck, set_var, num_sets, set_sizes, \
                                       dead_cards, num_iter, action)	\
do {                                                    	\
  int _i, _j, _k, _c;                                           \
  								\
  for (_i=0; _i<num_iter; _i++) {				\
    deck##_CardMask _used;					\
    _used = dead_cards;						\
    for (_j=0; _j<num_sets; _j++) {				\
      deck##_CardMask_RESET(set_var[_j]);			\
      for (_k=0; _k<set_sizes[_j]; _k++) {			\
        do {							\
          _c = RANDOM() % deck##_N_CARDS;			\
        } while (deck##_CardMask_CARD_IS_SET(_used, _c));	\
        deck##_CardMask_SET(set_var[_j], _c);			\
        deck##_CardMask_SET(_used, _c);				\
      }								\
    }								\
    { action };                                         	\
  };                                                    	\
} while (0)

#define ENUMERATE_1_CARDS(c,a) DECK_ENUMERATE_1_CARDS(Deck, c, a)
#define ENUMERATE_2_CARDS(c,a) DECK_ENUMERATE_2_CARDS(Deck, c, a)
#define ENUMERATE_3_CARDS(c,a) DECK_ENUMERATE_3_CARDS(Deck, c, a)
#define ENUMERATE_4_CARDS(c,a) DECK_ENUMERATE_4_CARDS(Deck, c, a)
#define ENUMERATE_5_CARDS(c,a) DECK_ENUMERATE_5_CARDS(Deck, c, a)
#define ENUMERATE_7_CARDS(c,a) DECK_ENUMERATE_7_CARDS(Deck, c, a)

#define ENUMERATE_1_CARDS_D(c,d,a) DECK_ENUMERATE_1_CARDS_D(Deck, c, d, a)
#define ENUMERATE_2_CARDS_D(c,d,a) DECK_ENUMERATE_2_CARDS_D(Deck, c, d, a)
#define ENUMERATE_3_CARDS_D(c,d,a) DECK_ENUMERATE_3_CARDS_D(Deck, c, d, a)
#define ENUMERATE_4_CARDS_D(c,d,a) DECK_ENUMERATE_4_CARDS_D(Deck, c, d, a)
#define ENUMERATE_5_CARDS_D(c,d,a) DECK_ENUMERATE_5_CARDS_D(Deck, c, d, a)
#define ENUMERATE_7_CARDS_D(c,d,a) DECK_ENUMERATE_7_CARDS_D(Deck, c, d, a)

#define ENUMERATE_N_CARDS(c,n,a) DECK_ENUMERATE_N_CARDS(Deck, c, n, a)

#define ENUMERATE_N_CARDS_D(c,n,d,a) \
  DECK_ENUMERATE_N_CARDS_D(Deck, c, n, d, a)

#define ENUMERATE_PERMUTATIONS_D(s, n, ss, dc, a) \
  DECK_ENUMERATE_PERMUTATIONS(Deck, s, n, ss, dc, a)

#define MONTECARLO_N_CARDS_D(c,n,d,nc,ni,a) \
  DECK_MONTECARLO_N_CARDS_D(Deck, c, n, d, nc, ni, a)

#define MONTECARLO_PERMUTATIONS_D(s, n, ss, dc, ni, a) \
  DECK_MONTECARLO_PERMUTATIONS(Deck, s, n, ss, dc, ni, a)


/* include/game_std.h */
#define DECK_STANDARD
#define RULES_STANDARD


/* include/deck_std.h */
/* MUST be lower than STRING_CARDS from lib/deck.c */
#define StdDeck_N_CARDS      52
#define StdDeck_MASK(index)  (StdDeck_cardMasksTable[index])

#define StdDeck_Rank_2      0
#define StdDeck_Rank_3      1
#define StdDeck_Rank_4      2
#define StdDeck_Rank_5      3
#define StdDeck_Rank_6      4
#define StdDeck_Rank_7      5
#define StdDeck_Rank_8      6
#define StdDeck_Rank_9      7
#define StdDeck_Rank_TEN    8
#define StdDeck_Rank_JACK   9
#define StdDeck_Rank_QUEEN  10
#define StdDeck_Rank_KING   11
#define StdDeck_Rank_ACE    12
#define StdDeck_Rank_COUNT  13
#define StdDeck_Rank_FIRST  StdDeck_Rank_2
#define StdDeck_Rank_LAST   StdDeck_Rank_ACE
#define StdDeck_N_RANKMASKS (1 << StdDeck_Rank_COUNT)

#define StdDeck_RANK(index)  ((index) % StdDeck_Rank_COUNT)
#define StdDeck_SUIT(index)  ((index) / StdDeck_Rank_COUNT)
#define StdDeck_MAKE_CARD(rank, suit) ((suit * StdDeck_Rank_COUNT) + rank)

#define StdDeck_Suit_HEARTS   0
#define StdDeck_Suit_DIAMONDS 1
#define StdDeck_Suit_CLUBS    2
#define StdDeck_Suit_SPADES   3
#define StdDeck_Suit_FIRST    StdDeck_Suit_HEARTS
#define StdDeck_Suit_LAST     StdDeck_Suit_SPADES
#define StdDeck_Suit_COUNT    4

typedef uint32 StdDeck_RankMask;

typedef union {
#ifdef USE_INT64
  uint64  cards_n;
#else
  struct {
    uint32 n1, n2;
  } cards_nn;
#endif
  struct {
    /* There are multiple ways to define these fields.  We could pack the
       13-bit fields together, we could define 13-bit fields with 3-bit
       padding between them, or we can define them as 16-bit fields.  
       Which is best will depend on the particular characteristics of the
       processor.  
       If we are on a big-endian processor, the padding should precede the
       field; on a little-endian processor, the padding should come after
       the field.  
       I found that uint32 was faster than uint16 on a lot of processors --
       the 16-bit instructions can be slow. 
    */
#ifdef WORDS_BIGENDIAN
    uint32         : 3;
    uint32 spades  :13;
    uint32         : 3;
    uint32 clubs   :13;
    uint32         : 3;
    uint32 diamonds:13;
    uint32         : 3;
    uint32 hearts  :13;
#else
    uint32 spades  :13;
    uint32         : 3;
    uint32 clubs   :13;
    uint32         : 3;
    uint32 diamonds:13;
    uint32         : 3;
    uint32 hearts  :13;
    uint32         : 3;
#endif
  } cards;
} StdDeck_CardMask;

#define StdDeck_CardMask_SPADES(cm)   ((cm).cards.spades)
#define StdDeck_CardMask_CLUBS(cm)    ((cm).cards.clubs)
#define StdDeck_CardMask_DIAMONDS(cm) ((cm).cards.diamonds)
#define StdDeck_CardMask_HEARTS(cm)   ((cm).cards.hearts)

#define StdDeck_CardMask_SET_SPADES(cm, ranks)   ((cm).cards.spades=(ranks))
#define StdDeck_CardMask_SET_CLUBS(cm, ranks)    ((cm).cards.clubs=(ranks))
#define StdDeck_CardMask_SET_DIAMONDS(cm, ranks) ((cm).cards.diamonds=(ranks))
#define StdDeck_CardMask_SET_HEARTS(cm, ranks)   ((cm).cards.hearts=(ranks))

#ifdef USE_INT64
#define StdDeck_CardMask_OP(result, op1, op2, OP) \
  LongLong_OP((result).cards_n, (op1).cards_n, (op2).cards_n, OP);
#else
#define StdDeck_CardMask_OP(result, op1, op2, OP) \
  do {                                                                  \
    (result.cards_nn.n1) = (op1.cards_nn.n1) OP (op2.cards_nn.n1);      \
    (result.cards_nn.n2) = (op1.cards_nn.n2) OP (op2.cards_nn.n2);      \
} while (0)
#endif

#ifdef USE_INT64
#define StdDeck_CardMask_NOT(result, op1)                               \
  do {                                                                  \
    (result).cards_n = ~(op1).cards_n;                                  \
  } while (0)
#else
#define StdDeck_CardMask_NOT(result, op1)                               \
  do {                                                                  \
    (result).cards_nn.n1 = ~(op1).cards_nn.n1;                          \
    (result).cards_nn.n2 = ~(op1).cards_nn.n2;                          \
  } while (0)
#endif

#define StdDeck_CardMask_OR(result, op1, op2) \
  StdDeck_CardMask_OP(result, op1, op2, |)

#define StdDeck_CardMask_AND(result, op1, op2) \
  StdDeck_CardMask_OP(result, op1, op2, &)

#define StdDeck_CardMask_XOR(result, op1, op2) \
  StdDeck_CardMask_OP(result, op1, op2, ^)

#define StdDeck_CardMask_SET(mask, index)       \
do {                                            \
  StdDeck_CardMask _t1 = StdDeck_MASK(index);           \
  StdDeck_CardMask_OR((mask), (mask), _t1);             \
} while (0)

#define StdDeck_CardMask_UNSET(mask, index)       	\
do {                                            	\
  StdDeck_CardMask _t1 = StdDeck_MASK(index);           \
  StdDeck_CardMask_NOT(_t1, _t1);	             	\
  StdDeck_CardMask_AND((mask), (mask), _t1);            \
} while (0)

#ifdef USE_INT64                                                          
#define StdDeck_CardMask_CARD_IS_SET(mask, index)                       \
  (( (mask).cards_n & (StdDeck_MASK(index).cards_n)) != 0 )                 
#else                                                                   
/* TODO: this looks wrong; should be ((mask.n1 & i.n1 != 0) || (i.n1 == 0)) */
#define StdDeck_CardMask_CARD_IS_SET(mask, index)                       \
  ((( (mask).cards_nn.n1 & (StdDeck_MASK(index).cards_nn.n1)) != 0 )    \
   || (( (mask).cards_nn.n2 & (StdDeck_MASK(index).cards_nn.n2)) != 0 ))   
#endif

#ifdef USE_INT64                                                          
#define StdDeck_CardMask_ANY_SET(mask1, mask2)                          \
  (( (mask1).cards_n & (mask2).cards_n) != 0 )                 
#else                                                                   
#define StdDeck_CardMask_ANY_SET(mask1, mask2)                           \
  ((( (mask1).cards_nn.n1 & (mask2).cards_nn.n1) != 0 )                 \
   || (( (mask1).cards_nn.n2 & (mask2).cards_nn.n2) != 0 ))           
#endif

#ifdef USE_INT64
#define StdDeck_CardMask_RESET(mask) \
  do { (mask).cards_n = 0; } while (0)
#else
#define StdDeck_CardMask_RESET(mask) \
  do { (mask).cards_nn.n1 = (mask).cards_nn.n2 = 0; } while (0)
#endif

#ifdef USE_INT64
#define StdDeck_CardMask_IS_EMPTY(mask) \
  ((mask).cards_n == 0)
#else
#define StdDeck_CardMask_IS_EMPTY(mask) \
  ((mask).cards_nn.n1 == 0 && (mask).cards_nn.n2 == 0)
#endif

#ifdef USE_INT64
#define StdDeck_CardMask_EQUAL(mask1, mask2) \
  ((mask1).cards_n == (mask2).cards_n)
#else
#define StdDeck_CardMask_EQUAL(mask1, mask2) \
  ((mask1).cards_nn.n1 == (mask2).cards_nn.n1 && (mask1).cards_nn.n2 == (mask2).cards_nn.n2)
#endif

/*
#ifdef __cplusplus
extern "C" {
#endif
*/
extern POKEREVAL_EXPORT uint8             nBitsTable[StdDeck_N_RANKMASKS];
extern POKEREVAL_EXPORT uint32     topFiveCardsTable[StdDeck_N_RANKMASKS];
extern POKEREVAL_EXPORT uint32       topFiveBitTable[StdDeck_N_RANKMASKS];
extern POKEREVAL_EXPORT uint8           topCardTable[StdDeck_N_RANKMASKS];
extern POKEREVAL_EXPORT uint32           topBitTable[StdDeck_N_RANKMASKS];
extern POKEREVAL_EXPORT uint32       topTwoBitsTable[StdDeck_N_RANKMASKS];
extern POKEREVAL_EXPORT uint32      topFiveBitsTable[StdDeck_N_RANKMASKS];
extern POKEREVAL_EXPORT uint8          straightTable[StdDeck_N_RANKMASKS];
/*
#ifdef __cplusplus
}
#endif
*/
extern POKEREVAL_EXPORT uint32  bottomFiveCardsTable[StdDeck_N_RANKMASKS];
extern POKEREVAL_EXPORT uint32  bottomFiveJokerTable[StdDeck_N_RANKMASKS];
extern POKEREVAL_EXPORT uint8        bottomCardTable[StdDeck_N_RANKMASKS];

extern POKEREVAL_EXPORT StdDeck_CardMask StdDeck_cardMasksTable[StdDeck_N_CARDS];

extern POKEREVAL_EXPORT char StdDeck_rankChars[StdDeck_Rank_LAST+1];
extern POKEREVAL_EXPORT char StdDeck_suitChars[StdDeck_Suit_LAST+1];

extern POKEREVAL_EXPORT int StdDeck_cardToString(int cardIndex, char *outString);
extern POKEREVAL_EXPORT int StdDeck_stringToCard(char *inString, int *outCard);

#define StdDeck_cardString(i) GenericDeck_cardString(&StdDeck, (i))
#define StdDeck_printCard(i)  GenericDeck_printCard(&StdDeck, (i))
#define StdDeck_printMask(m)  GenericDeck_printMask(&StdDeck, ((void *) &(m)))
#define StdDeck_maskString(m) GenericDeck_maskString(&StdDeck, ((void *) &(m)))
#define StdDeck_numCards(m) GenericDeck_numCards(&StdDeck, ((void *) &(m)))
#define StdDeck_maskToString(m, s) GenericDeck_maskToString(&StdDeck, ((void *) &(m)), (s))

extern POKEREVAL_EXPORT Deck StdDeck;


#endif


#ifdef DECK_STANDARD

#if defined(Deck_N_CARDS)
/* include/deck_undef.h */
#undef Deck_N_CARDS      
#undef Deck_MASK         
#undef Deck_RANK         
#undef Deck_SUIT         

#undef Rank_2            
#undef Rank_3            
#undef Rank_4            
#undef Rank_5            
#undef Rank_6            
#undef Rank_7            
#undef Rank_8            
#undef Rank_9            
#undef Rank_TEN          
#undef Rank_JACK         
#undef Rank_QUEEN        
#undef Rank_KING         
#undef Rank_ACE          
#undef Rank_FIRST        
#undef Rank_COUNT        

#undef Suit_HEARTS       
#undef Suit_DIAMONDS     
#undef Suit_CLUBS        
#undef Suit_SPADES       
#undef Suit_FIRST        
#undef Suit_COUNT        

#undef CardMask               
#undef CardMask_OR            
#undef CardMask_SET           
#undef CardMask_CARD_IS_SET   
#undef CardMask_ANY_SET       
#undef CardMask_RESET         
#undef CardMask_NOT
#undef CardMask_XOR
#undef CardMask_AND
#undef CardMask_UNSET

#undef CardMask_SPADES        
#undef CardMask_HEARTS        
#undef CardMask_CLUBS         
#undef CardMask_DIAMONDS      
#undef CardMask_SET_SPADES        
#undef CardMask_SET_HEARTS        
#undef CardMask_SET_CLUBS         
#undef CardMask_SET_DIAMONDS      

#undef Deck_cardToString
#undef Deck_maskToString
#undef Deck_printCard
#undef Deck_printMask

#undef CurDeck
#endif

#define Deck_N_CARDS      StdDeck_N_CARDS
#define Deck_MASK         StdDeck_MASK
#define Deck_RANK         StdDeck_RANK
#define Deck_SUIT         StdDeck_SUIT

#define Rank_2            StdDeck_Rank_2 
#define Rank_3            StdDeck_Rank_3
#define Rank_4            StdDeck_Rank_4 
#define Rank_5            StdDeck_Rank_5 
#define Rank_6            StdDeck_Rank_6 
#define Rank_7            StdDeck_Rank_7 
#define Rank_8            StdDeck_Rank_8 
#define Rank_9            StdDeck_Rank_9 
#define Rank_TEN          StdDeck_Rank_TEN
#define Rank_JACK         StdDeck_Rank_JACK
#define Rank_QUEEN        StdDeck_Rank_QUEEN
#define Rank_KING         StdDeck_Rank_KING
#define Rank_ACE          StdDeck_Rank_ACE
#define Rank_FIRST        StdDeck_Rank_FIRST 
#define Rank_COUNT        StdDeck_Rank_COUNT

#define Suit_HEARTS       StdDeck_Suit_HEARTS
#define Suit_DIAMONDS     StdDeck_Suit_DIAMONDS
#define Suit_CLUBS        StdDeck_Suit_CLUBS
#define Suit_SPADES       StdDeck_Suit_SPADES
#define Suit_FIRST        StdDeck_Suit_FIRST
#define Suit_COUNT        StdDeck_Suit_COUNT

#define CardMask               StdDeck_CardMask 
#define CardMask_NOT           StdDeck_CardMask_NOT
#define CardMask_OR            StdDeck_CardMask_OR
#define CardMask_XOR           StdDeck_CardMask_XOR
#define CardMask_AND           StdDeck_CardMask_AND
#define CardMask_SET           StdDeck_CardMask_SET
#define CardMask_CARD_IS_SET   StdDeck_CardMask_CARD_IS_SET
#define CardMask_ANY_SET       StdDeck_CardMask_ANY_SET
#define CardMask_RESET         StdDeck_CardMask_RESET
#define CardMask_UNSET         StdDeck_CardMask_UNSET

#define CardMask_SPADES        StdDeck_CardMask_SPADES
#define CardMask_HEARTS        StdDeck_CardMask_HEARTS
#define CardMask_CLUBS         StdDeck_CardMask_CLUBS
#define CardMask_DIAMONDS      StdDeck_CardMask_DIAMONDS

#define CardMask_SET_SPADES    StdDeck_CardMask_SET_SPADES
#define CardMask_SET_HEARTS    StdDeck_CardMask_SET_HEARTS
#define CardMask_SET_CLUBS     StdDeck_CardMask_SET_CLUBS
#define CardMask_SET_DIAMONDS  StdDeck_CardMask_SET_DIAMONDS

#define CurDeck StdDeck

/* include/rules_std.h */
#define StdRules_HandType_NOPAIR    0
#define StdRules_HandType_ONEPAIR   1
#define StdRules_HandType_TWOPAIR   2
#define StdRules_HandType_TRIPS     3
#define StdRules_HandType_STRAIGHT  4
#define StdRules_HandType_FLUSH     5
#define StdRules_HandType_FULLHOUSE 6
#define StdRules_HandType_QUADS     7
#define StdRules_HandType_STFLUSH   8
#define StdRules_HandType_FIRST     StdRules_HandType_NOPAIR
#define StdRules_HandType_LAST      StdRules_HandType_STFLUSH
#define StdRules_HandType_COUNT     9

#define StdRules_FIVE_STRAIGHT \
 ((1 << StdDeck_Rank_ACE ) \
  | (1 << StdDeck_Rank_2 ) \
  | (1 << StdDeck_Rank_3 ) \
  | (1 << StdDeck_Rank_4 ) \
  | (1 << StdDeck_Rank_5 ))

extern POKEREVAL_EXPORT const char *StdRules_handTypeNames[StdRules_HandType_LAST+1];
extern POKEREVAL_EXPORT const char *StdRules_handTypeNamesPadded[StdRules_HandType_LAST+1];

extern POKEREVAL_EXPORT int StdRules_nSigCards[StdRules_HandType_LAST+1];

extern POKEREVAL_EXPORT int StdRules_HandVal_toString(HandVal handval, char *outString); 
extern POKEREVAL_EXPORT int StdRules_HandVal_print(HandVal handval);

#endif

#ifdef RULES_STANDARD

#if defined(HandType_COUNT)
/* include/rules_undef.h */
#undef HandType_NOPAIR
#undef HandType_ONEPAIR
#undef HandType_TWOPAIR
#undef HandType_TRIPS
#undef HandType_STRAIGHT
#undef HandType_FLUSH
#undef HandType_FULLHOUSE
#undef HandType_QUADS
#undef HandType_STFLUSH
#undef HandType_FIRST
#undef HandType_COUNT
#undef HandType_LAST
#undef handTypeNames
#undef handTypeNamesPadded
#undef nSigCards
#undef HandVal_print
#undef HandVal_toString
#endif

#define HandType_NOPAIR    StdRules_HandType_NOPAIR
#define HandType_ONEPAIR   StdRules_HandType_ONEPAIR
#define HandType_TWOPAIR   StdRules_HandType_TWOPAIR
#define HandType_TRIPS     StdRules_HandType_TRIPS
#define HandType_STRAIGHT  StdRules_HandType_STRAIGHT
#define HandType_FLUSH     StdRules_HandType_FLUSH
#define HandType_FULLHOUSE StdRules_HandType_FULLHOUSE
#define HandType_QUADS     StdRules_HandType_QUADS
#define HandType_STFLUSH   StdRules_HandType_STFLUSH
#define HandType_FIRST     StdRules_HandType_FIRST
#define HandType_COUNT     StdRules_HandType_COUNT
#define HandType_LAST      StdRules_HandType_LAST

#define handTypeNames        StdRules_handTypeNames
#define handTypeNamesPadded  StdRules_handTypeNamesPadded
#define nSigCards            StdRules_nSigCards
#define HandVal_print        StdRules_HandVal_print
#define HandVal_toString     StdRules_HandVal_toString

#undef Hand_EVAL_N
#undef Hand_EVAL_LOW
#undef Hand_EVAL_LOW8

#define Hand_EVAL_N     StdDeck_StdRules_EVAL_N
#define Hand_EVAL_TYPE  StdDeck_StdRules_EVAL_TYPE
#define Hand_EVAL_X5    StdDeck_StdRules_EVAL_X5
#define Hand_EVAL_X7    StdDeck_StdRules_EVAL_X7

#define Hand_EVAL_LOW   StdDeck_Lowball_EVAL
#define Hand_EVAL_LOW8  StdDeck_Lowball8_EVAL

#undef  DECK_STANDARD
#undef  RULES_STANDARD


HandVal StdDeck_StdRules_EVAL_N( StdDeck_CardMask cards, int n_cards )



#ifdef __cplusplus
}
#endif

#endif /* ISL_INCLUDE_POKER_EVAL_H_ */


#ifdef ISL_POKER_EVAL_IMPLEMENTATION
/* include/inline/eval.h */
/*
 * When run over seven cards, here are the distribution of hands:
 *        high hand: 23294460
 *             pair: 58627800
 *         two pair: 31433400
 *  three of a kind: 6461620
 *         straight: 6180020
 *            flush: 4047644
 *       full house: 3473184
 *   four of a kind: 224848
 *   straight flush: 41584
 *
 */

#define SC sc
#define SD sd
#define SH sh
#define SS ss

/*
 * is_straight used to check for a straight by masking the ranks with four
 * copies of itself, each shifted one bit with respect to the
 * previous one.  So any sequence of five adjacent bits will still
 * be non-zero, but any gap will result in a zero value.  There's
 * a nice side-effect of leaving the top most bit set so we can use
 * it to set top_card.
 * Now we use a precomputed lookup table.  
 *
 */

#if 0
/* Keith's is-straight, which is still pretty good and uses one less table. */
    if ( (ranks2  = ranks & (ranks << 1)) &&
	 (ranks2 &=         (ranks << 2)) &&
	 (ranks2 &=         (ranks << 3)) &&
	 (ranks2 &=         (ranks << 4)) ) {
        retval.eval_t.hand     = StdRules_HandType_STRAIGHT;
        retval.eval_t.top_card = topCardTable[ranks2];
    } else if ((ranks & StdDeck_FIVE_STRAIGHT) ==  StdDeck_FIVE_STRAIGHT) {
        retval.eval_t.hand     = StdRules_HandType_STRAIGHT;
        retval.eval_t.top_card = StdDeck_Ranks_5;
    }
#endif


HandVal StdDeck_StdRules_EVAL_N( StdDeck_CardMask cards, int n_cards )
{
  HandVal retval;
  uint32 ranks, four_mask, three_mask, two_mask, 
    n_dups, n_ranks;
  uint32 sc, sd, sh, ss;

  ss = StdDeck_CardMask_SPADES(cards);
  sc = StdDeck_CardMask_CLUBS(cards);
  sd = StdDeck_CardMask_DIAMONDS(cards);
  sh = StdDeck_CardMask_HEARTS(cards);

  retval = 0;
  ranks = SC | SD | SH | SS;
  n_ranks = nBitsTable[ranks];
  n_dups = n_cards - n_ranks;

  /* Check for straight, flush, or straight flush, and return if we can
     determine immediately that this is the best possible hand 
  */
  if (n_ranks >= 5) {
    if (nBitsTable[SS] >= 5) {
      if (straightTable[SS]) 
        return HandVal_HANDTYPE_VALUE(StdRules_HandType_STFLUSH)
          + HandVal_TOP_CARD_VALUE(straightTable[SS]);
      else
        retval = HandVal_HANDTYPE_VALUE(StdRules_HandType_FLUSH) 
          + topFiveCardsTable[SS];
    } 
    else if (nBitsTable[SC] >= 5) {
      if (straightTable[SC]) 
        return HandVal_HANDTYPE_VALUE(StdRules_HandType_STFLUSH)
          + HandVal_TOP_CARD_VALUE(straightTable[SC]);
      else 
        retval = HandVal_HANDTYPE_VALUE(StdRules_HandType_FLUSH) 
          + topFiveCardsTable[SC];
    } 
    else if (nBitsTable[SD] >= 5) {
      if (straightTable[SD]) 
        return HandVal_HANDTYPE_VALUE(StdRules_HandType_STFLUSH)
          + HandVal_TOP_CARD_VALUE(straightTable[SD]);
      else 
        retval = HandVal_HANDTYPE_VALUE(StdRules_HandType_FLUSH) 
          + topFiveCardsTable[SD];
    } 
    else if (nBitsTable[SH] >= 5) {
      if (straightTable[SH]) 
        return HandVal_HANDTYPE_VALUE(StdRules_HandType_STFLUSH)
          + HandVal_TOP_CARD_VALUE(straightTable[SH]);
      else 
        retval = HandVal_HANDTYPE_VALUE(StdRules_HandType_FLUSH) 
          + topFiveCardsTable[SH];
    } 
    else {
      int st;

      st = straightTable[ranks];
      if (st) 
        retval = HandVal_HANDTYPE_VALUE(StdRules_HandType_STRAIGHT)
          + HandVal_TOP_CARD_VALUE(st);
    };

    /* Another win -- if there can't be a FH/Quads (n_dups < 3), 
       which is true most of the time when there is a made hand, then if we've
       found a five card hand, just return.  This skips the whole process of
       computing two_mask/three_mask/etc.
    */
    if (retval && n_dups < 3)
      return retval;
  };

  /*
   * By the time we're here, either: 
     1) there's no five-card hand possible (flush or straight), or
     2) there's a flush or straight, but we know that there are enough
        duplicates to make a full house / quads possible.  
   */
  switch (n_dups)
    {
    case 0:
      /* It's a no-pair hand */
      return HandVal_HANDTYPE_VALUE(StdRules_HandType_NOPAIR)
        + topFiveCardsTable[ranks];
      break;
      
    case 1: {
      /* It's a one-pair hand */
      uint32 t, kickers;

      two_mask   = ranks ^ (SC ^ SD ^ SH ^ SS);

      retval = HandVal_HANDTYPE_VALUE(StdRules_HandType_ONEPAIR)
        + HandVal_TOP_CARD_VALUE(topCardTable[two_mask]);
      t = ranks ^ two_mask;      /* Only one bit set in two_mask */
      /* Get the top five cards in what is left, drop all but the top three 
       * cards, and shift them by one to get the three desired kickers */
      kickers = (topFiveCardsTable[t] >> HandVal_CARD_WIDTH)
        & ~HandVal_FIFTH_CARD_MASK;
      retval += kickers;

      return retval;
    }
    break;
      
    case 2: 
      /* Either two pair or trips */

      two_mask   = ranks ^ (SC ^ SD ^ SH ^ SS);
      if (two_mask) { 
        uint32 t;

        t = ranks ^ two_mask; /* Exactly two bits set in two_mask */
        retval = HandVal_HANDTYPE_VALUE(StdRules_HandType_TWOPAIR)
          + (topFiveCardsTable[two_mask]
             & (HandVal_TOP_CARD_MASK | HandVal_SECOND_CARD_MASK))
          + HandVal_THIRD_CARD_VALUE(topCardTable[t]);

        return retval;
      }
      else {
        int t, second;
        
        three_mask = (( SC&SD )|( SH&SS )) & (( SC&SH )|( SD&SS ));
        
        retval = HandVal_HANDTYPE_VALUE(StdRules_HandType_TRIPS)
          + HandVal_TOP_CARD_VALUE(topCardTable[three_mask]);

        t = ranks ^ three_mask; /* Only one bit set in three_mask */
        second = topCardTable[t];
        retval += HandVal_SECOND_CARD_VALUE(second);
        t ^= (1 << second);
        retval += HandVal_THIRD_CARD_VALUE(topCardTable[t]);
        return retval;
      }
      break;
      
    default:
      /* Possible quads, fullhouse, straight or flush, or two pair */
      four_mask  = SH & SD & SC & SS;
      if (four_mask) {
        int tc;

        tc = topCardTable[four_mask];
        retval = HandVal_HANDTYPE_VALUE(StdRules_HandType_QUADS)
          + HandVal_TOP_CARD_VALUE(tc)
          + HandVal_SECOND_CARD_VALUE(topCardTable[ranks ^ (1 << tc)]);
        return retval;
      };

      /* Technically, three_mask as defined below is really the set of
         bits which are set in three or four of the suits, but since
         we've already eliminated quads, this is OK */
      /* Similarly, two_mask is really two_or_four_mask, but since we've
         already eliminated quads, we can use this shortcut */

      two_mask   = ranks ^ (SC ^ SD ^ SH ^ SS);
      if (nBitsTable[two_mask] != n_dups) {
        /* Must be some trips then, which really means there is a 
           full house since n_dups >= 3 */
        int tc, t;

        three_mask = (( SC&SD )|( SH&SS )) & (( SC&SH )|( SD&SS ));
        retval  = HandVal_HANDTYPE_VALUE(StdRules_HandType_FULLHOUSE);
        tc = topCardTable[three_mask];
        retval += HandVal_TOP_CARD_VALUE(tc);
        t = (two_mask | three_mask) ^ (1 << tc);
        retval += HandVal_SECOND_CARD_VALUE(topCardTable[t]);
        return retval;
      };

      if (retval) /* flush and straight */
        return retval;
      else {
        /* Must be two pair */
        int top, second;
          
        retval = HandVal_HANDTYPE_VALUE(StdRules_HandType_TWOPAIR);
        top = topCardTable[two_mask];
        retval += HandVal_TOP_CARD_VALUE(top);
        second = topCardTable[two_mask ^ (1 << top)];
        retval += HandVal_SECOND_CARD_VALUE(second);
        retval += HandVal_THIRD_CARD_VALUE(topCardTable[ranks ^ (1 << top) 
                                                        ^ (1 << second)]);
        return retval;
      };

      break;
    };

  /* Should never happen */
  assert(!"Logic error in StdDeck_StdRules_EVAL_N");
}

#undef SC
#undef SH
#undef SD
#undef SS
#endif /* ISL_POKER_EVAL_IMPLEMENTATION */
