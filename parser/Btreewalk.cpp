#include <Bexecinfo.h>
#include <Alognode.h>
#include <Aphynode.h>
#include <Alogprop.h>
#include <Aphyprop.h>
#include <Aopinc.h>
#include <Bprojlist.h>
#include <Bextent.h>

#include <Bbogus.h>

void Bblanks (int n, ostream &os)
{
  for (int i=0; i<n; i++)
    os << ' ';
}

#ifdef __GNUC__
template <class T>
void Bprintset (ostream &os, Aset_t<T> set)
{
  FOR_EACH_ELEMENT_OF_SET (set)
    os << ' ' << set.CurrentElement ()->Number ();
}
#endif

void Afilescan_t::Execute (Bexec_info_t &exec_info)
{
  Bblanks (exec_info.indent (), std::cout);
  std::cout << GetName () << std::endl;
  Bblanks (exec_info.indent (), std::cout);
  std::cout << "relation " << ((Aget_t *)exec_info.op ())->rel ()->name () << " ("
       << ((Aget_t *)exec_info.op ())->rel ()->rel_var () << ")"; 
  // Bprintset ((ostream &)std::cout, ((Aget_t *)exec_info.op ())->operations ());
  std::cout << std::endl;

  exec_info.delete_inputs ();
}

void Aindexscan_t::Execute (Bexec_info_t &exec_info)
{
  Bblanks (exec_info.indent (), std::cout);
  std::cout << GetName () << std::endl;
  Bblanks (exec_info.indent (), std::cout);
  // std::cout << "oprns"; 
  // Bprintset ((ostream &)std::cout, 
  // ((Aidx_collapse_t *)exec_info.op ())->operations ());
  
  std::cout << "index " 
       << Aglob_vars ()->cat->idxname (idxid ()) << ":: ";
  Aset_t<Aptree_t> oprns = ((Aidx_collapse_t *)exec_info.op ())->operations ();
  int is_first = 1;
  FOR_EACH_ELEMENT_OF_SET (oprns)
    {
      Aptree_t *oprn = oprns.CurrentElement ();
      if (oprn->is_relop ())
	{
	  if (is_first)
	    is_first = 0;
	  else
	    std::cout << " AND ";
	  
	  std::cout << *oprn;
	}
    }
  std::cout << std::endl;

  exec_info.delete_inputs ();
}

void Afilter_t::Execute (Bexec_info_t &exec_info)
{
  exec_info.compute_inputs_for_select_operator ();

  Bblanks (exec_info.indent (), std::cout);
  std::cout << GetName () << std::endl;
  Bblanks (exec_info.indent (), std::cout);
  // std::cout << "oprns"; 
  // Bprintset ((ostream &)std::cout, ((Aselect_t *)exec_info.op ())->operations ());
  Aset_t<Aptree_t> oprns = ((Aselect_t *)exec_info.op ())->operations ();
  int is_first = 1;
  FOR_EACH_ELEMENT_OF_SET (oprns)
    {
      Aptree_t *oprn = oprns.CurrentElement ();
      if (oprn->is_relop ())
	{
	  if (is_first)
	    is_first = 0;
	  else
	    std::cout << " AND ";
	  
	  std::cout << *oprn;
	}
    }
  std::cout << std::endl;

  exec_info.delete_inputs ();
}

void Aassembly_t::Execute (Bexec_info_t &exec_info)
{
  exec_info.compute_inputs_for_simple_operator ();
  Bblanks (exec_info.indent (), std::cout);
  std::cout << GetName () << std::endl;
  Bblanks (exec_info.indent (), std::cout);
  // std::cout << "oprns"; 
  // Bprintset ((ostream &)std::cout, ((Aassembly_t *)exec_info.algo ())->tuplerefs ());
  Aset_t<Aptree_t> oprns = tuplerefs ();
  int is_first = 1;
  FOR_EACH_ELEMENT_OF_SET (oprns)
    {
      Aptree_t *oprn = oprns.CurrentElement ();
      assert (oprn->is_tupleref ());
      if (is_first)
	is_first = 0;
      else
	std::cout << " AND ";
	  
      std::cout << *oprn;
    }
  std::cout << std::endl;

  exec_info.delete_inputs ();
}

void Ahh_join_t::Execute (Bexec_info_t &exec_info)
{
  int inverse = ((Ajoin_t *)exec_info.op ())->inverse ();
  exec_info.compute_inputs_for_join_operator ();
  Bblanks (exec_info.indent (), std::cout);
  std::cout << "hash_join" << std::endl;
  Bblanks (exec_info.indent (), std::cout);
    // std::cout << "oprns"; 
  // Bprintset ((ostream &)std::cout, ((Ajoin_t *)exec_info.op ())->operations ());
  Aset_t<Aptree_t> oprns = ((Ajoin_t *)exec_info.op ())->operations ();
  int is_first = 1;
  FOR_EACH_ELEMENT_OF_SET (oprns)
    {
      Aptree_t *oprn = oprns.CurrentElement ();
      if (oprn->is_relop () || oprn->is_tupleref ())
	{
	  if (is_first)
	    is_first = 0;
	  else
	    std::cout << " AND ";
	  
	  if (oprn->is_tupleref ()) 
	    std::cout << *oprn << " = " << *oprn;
	  else
	    std::cout << *oprn;
	}
    }

    if (inverse) std::cout << " (inverse)";
  std::cout << std::endl;

  exec_info.delete_inputs ();
}

void Ahhptr_join_t::Execute (Bexec_info_t &exec_info)
{
  int inverse = ((Ajoin_t *)exec_info.op ())->inverse ();
  exec_info.compute_inputs_for_simple_operator ();

  Bblanks (exec_info.indent () + 2, std::cout);
  Arel_t *input_relation = 
    ((Aget_t *)(exec_info.node ()->RightInput ()->GetParent ()->GetOp ()))->rel ();
  const char *input_relation_name = input_relation->name ();
  const char *input_relvar_name = input_relation->rel_var ();
  std::cout << "filescan" << std::endl;
  Bblanks (exec_info.indent () + 2, std::cout);
  std::cout << "relation " << input_relation_name 
       << " (" << input_relvar_name << ")" << std::endl;


  Bblanks (exec_info.indent (), std::cout);
  std::cout << "ptr_join" << std::endl;
  // std::cout << "oprns"; 
  // Bprintset ((ostream &)std::cout, ((Ajoin_t *)exec_info.op ())->operations ());
  Bblanks (exec_info.indent (), std::cout);
  Aset_t<Aptree_t> oprns = ((Ajoin_t *)exec_info.op ())->operations ();
  int is_first = 1;
  FOR_EACH_ELEMENT_OF_SET (oprns)
    {
      Aptree_t *oprn = oprns.CurrentElement ();
      if (oprn->is_relop () || oprn->is_tupleref ())
	{
	  if (is_first)
	    is_first = 0;
	  else
	    std::cout << " AND ";
	  
	  std::cout << *oprn;
	}
    }
    if (inverse) std::cout << " (inverse)";
  std::cout << std::endl;

  exec_info.delete_inputs ();
}

void Aunnestalgo_t::Execute (Bexec_info_t &exec_info)
{
  exec_info.compute_inputs_for_simple_operator ();
  Bblanks (exec_info.indent (), std::cout);
  std::cout << GetName () << std::endl;
  Bblanks (exec_info.indent (), std::cout);
  // std::cout << "oprns"; 
  // Bprintset ((ostream &)std::cout, ((Aunnestop_t *)exec_info.op ())->operations ());
  Aset_t<Aptree_t> oprns = ((Aunnestop_t *)exec_info.op ())->operations ();
  int is_first = 1;
  FOR_EACH_ELEMENT_OF_SET (oprns)
    {
      Aptree_t *oprn = oprns.CurrentElement ();
      if (is_first)
	is_first = 0;
      else
	std::cout << " AND ";
      
      std::cout << *oprn;
    }
  std::cout << std::endl;

  exec_info.delete_inputs ();
}

void Aoutputalgo_t::Execute (Bexec_info_t &exec_info)
{
  exec_info.compute_inputs_for_simple_operator ();
  Bblanks (exec_info.indent (), std::cout);
  std::cout << GetName () << ' ';
  Bblanks (exec_info.indent (), std::cout);
//  std::cout << "oprns"; 
//  Bprintset ((ostream &)std::cout, exec_info.op ()->operations ());
  std::cout << std::endl;

  exec_info.delete_inputs ();
}


