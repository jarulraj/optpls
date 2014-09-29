#include "Bextent.h"
#include <Aptree.h>


// Selection on all the tuples of the extent.
int Extent::select(const char*     extentName,
		   Aptree_t& predicatetree,
		   const char*     resExtentName,
		   P_Bool    tmpFlag,
		   const char*     attrSuffix,
		   ProjList& projList,
		   P_Bool    isAggregate)
{
  std::cout << "select " << extentName 
       << " [suff: " << (attrSuffix ? attrSuffix : "none") << "]"
       << " to " << resExtentName 
       << (tmpFlag == P_True ? "(tmp) " : " ") << std::endl;
  std::cout << "  pred: " << predicatetree << std::endl;
  std::cout << "  projlist: " << std::endl;
  if (projList.null_projlist ())
    std::cout << "    is NULL" << std::endl;
  else
    for (int i=0; i<projList.num (); i++)
      std::cout << "    " << projList.get (i).out_attrname << " as " 
	   << *projList.get (i).ptree << std::endl;
  std::cout << std::endl;
  return 0;
}

// Selection using an index.
int Extent::indexSelect(const char*     extentName,
			const char*     attrName,
			Aptree_t& idxPredTree,
			Aptree_t& auxPredTree,
			const char*     resExtentName,
			P_Bool    tmpFlag,
			const char*     attrSuffix,
			ProjList& projList)
{
  std::cout << "indexscan " << extentName << "::" << attrName 
       << " [suff: " << (attrSuffix ? attrSuffix : "none") << "]"
       << " to " << resExtentName 
       << (tmpFlag == P_True ? "(tmp) " : " ") << std::endl;
  std::cout << "  idxpred: " << idxPredTree << std::endl;
  std::cout << "  auxpreds: " << auxPredTree << std::endl;
  std::cout << "  projlist: " << std::endl;
  if (projList.null_projlist ())
    std::cout << "    is NULL" << std::endl;
  else
    for (int i=0; i<projList.num (); i++)
      std::cout << "    " << projList.get (i).out_attrname << " as " 
	   << *projList.get (i).ptree << std::endl;
  std::cout << std::endl;
  return 0;
}

// Block Nested-loops join
int Extent::nlJoin(const char*     outerExtentName,
		   const char*     innerExtentName,
		   Aptree_t& predicatetree,
		   const char*     resExtentName,
		   P_Bool    tmpFlag,
		   const char*     outerAttrSuffix,
		   const char*     innerAttrSuffix,
		   ProjList& projList)
{
  std::cout << "nl join " << outerExtentName 
       << " [suff: " << (outerAttrSuffix ? outerAttrSuffix : "none") << "]" 
       << " and " << innerExtentName 
       << " [suff: " << (innerAttrSuffix ? innerAttrSuffix : "none") << "]" 
       << " into " << resExtentName 
       << (tmpFlag == P_True ? "(tmp) " : " ") << std::endl;
  std::cout << "  pred: " << predicatetree << std::endl;
  std::cout << "  projlist: " << std::endl;
  if (projList.null_projlist ())
    std::cout << "    is NULL" << std::endl;
  else
    for (int i=0; i<projList.num (); i++)
      std::cout << "    " << projList.get (i).out_attrname << " as " 
	   << *projList.get (i).ptree << std::endl;
  std::cout << std::endl;
  return 0;
}
   
// Nested-loops indexed join
int Extent::nlIdxJoin(const char*     outerExtentName,
		      const char*     innerExtentName,
		      Aptree_t& idxPredTree,
		      Aptree_t& auxPredTree,
		      const char*     resExtentName,
		      P_Bool    tmpFlag,
		      const char*     outerAttrSuffix,
		      const char*     innerAttrSuffix,
		      ProjList& projList)
{
  std::cout << "idx join " << outerExtentName 
       << " [suff: " << (outerAttrSuffix ? outerAttrSuffix : "none") << "]" 
       << " and " << innerExtentName 
       << " [suff: " << (innerAttrSuffix ? innerAttrSuffix : "none") << "]" 
       << " into " << resExtentName 
       << (tmpFlag == P_True ? "(tmp) " : " ") << std::endl;
  std::cout << "  idxpred: " << idxPredTree << std::endl;
  std::cout << "  auxpreds: " << auxPredTree << std::endl;
  std::cout << "  projlist: " << std::endl;
  if (projList.null_projlist ())
    std::cout << "    is NULL" << std::endl;
  else
    for (int i=0; i<projList.num (); i++)
      std::cout << "    " << projList.get (i).out_attrname << " as " 
	   << *projList.get (i).ptree << std::endl;
  std::cout << std::endl;
  return 0;
}   
int Extent::mergeJoin(const char*     outerExtentName,
		      const char*     innerExtentName,
		      Aptree_t& idxPredTree,
		      Aptree_t& auxPredTree,
		      const char*     resExtentName,
		      P_Bool    tmpFlag,
		      const char*     outerAttrSuffix,
		      const char*     innerAttrSuffix,
		      ProjList& projList)
{
  std::cout << "merge join " << outerExtentName 
       << " [suff: " << (outerAttrSuffix ? outerAttrSuffix : "none") << "]" 
       << " and " << innerExtentName 
       << " [suff: " << (innerAttrSuffix ? innerAttrSuffix : "none") << "]" 
       << " into " << resExtentName 
       << (tmpFlag == P_True ? "(tmp) " : " ") << std::endl;
  std::cout << "  join pred: " << idxPredTree << std::endl;
  std::cout << "  auxpreds: " << auxPredTree << std::endl;
  std::cout << "  projlist: " << std::endl;
  if (projList.null_projlist ())
    std::cout << "    is NULL" << std::endl;
  else
    for (int i=0; i<projList.num (); i++)
      std::cout << "    " << projList.get (i).out_attrname << " as " 
	   << *projList.get (i).ptree << std::endl;
  std::cout << std::endl;
  return 0;
}   
int Extent::hashJoin(const char*     outerExtentName,
		     const char*     innerExtentName,
		     Aptree_t& idxPredTree,
		     Aptree_t& auxPredTree,
		     const char*     resExtentName,
		     P_Bool    tmpFlag,
		     const char*     outerAttrSuffix,
		     const char*     innerAttrSuffix,
		     ProjList& projList)
{
  std::cout << "hash join " << outerExtentName 
       << " [suff: " << (outerAttrSuffix ? outerAttrSuffix : "none") << "]" 
       << " and " << innerExtentName 
       << " [suff: " << (innerAttrSuffix ? innerAttrSuffix : "none") << "]" 
       << " into " << resExtentName 
       << (tmpFlag == P_True ? "(tmp) " : " ") << std::endl;
  std::cout << "  join pred: " << idxPredTree << std::endl;
  std::cout << "  auxpreds: " << auxPredTree << std::endl;
  std::cout << "  projlist: " << std::endl;
  if (projList.null_projlist ())
    std::cout << "    is NULL" << std::endl;
  else
    for (int i=0; i<projList.num (); i++)
      std::cout << "    " << projList.get (i).out_attrname << " as " 
	   << *projList.get (i).ptree << std::endl;
  std::cout << std::endl;
  return 0;
}   
// The sort operator.
int Extent::sortExtent(const char*     extentName,
		       const char*     attrName,
		       P_Bool    eliminateDup,
		       const char*     resExtentName,
		       P_Bool    tmpFlag,
		       ProjList &projList)
{
  std::cout << "sort " << extentName << "::" << attrName << " "
       << (eliminateDup == P_True ? " (" : " (no ") << "distinct) "
       << "into " << resExtentName 
       << (tmpFlag == P_True ? "(tmp) " : " ") << std::endl;
  if (projList.null_projlist ())
    std::cout << "    is NULL" << std::endl;
  else
    for (int i=0; i<projList.num (); i++)
      std::cout << "    " << projList.get (i).out_attrname << " as " 
	   << *projList.get (i).ptree << std::endl;
  std::cout << std::endl;
  return 0;
}
   
int Extent::aggregate(const char*     extentName,    
		      Aptree_t& ppPredTree,    
		      const char*     resExtentName, 
		      P_Bool    tmpFlag,       
		      const char*     attrSuffix,
		      ProjList& projList,
		      const char*     groupBy[],
		      int       numGroupByAttr)
{
  std::cout << "aggregate " << extentName 
       << " [suff: " << (attrSuffix ? attrSuffix : "none") << "]"
       << " to " << resExtentName 
       << (tmpFlag == P_True ? "(tmp) " : " ") << std::endl;
  std::cout << "  pred: " << ppPredTree << std::endl;
  std::cout << "  projlist: " << std::endl;
  if (projList.null_projlist ())
    std::cout << "    is NULL" << std::endl;
  else
    for (int i=0; i<projList.num (); i++)
      std::cout << "    " << projList.get (i).out_attrname << " as " 
	   << *projList.get (i).ptree << std::endl;
  std::cout << std::endl;
  return 0;
}

int Extent::update (const char *extentName,
		    Aptree_t& ppPredTree,
		    ProjList &projList)
{
  std::cout << "called update" << std::endl;
  return 0;
}
int Extent::insert (const char *extentName,
		    ProjList &projList)
{
  std::cout << "called insert" << std::endl;
  return 0;
}
