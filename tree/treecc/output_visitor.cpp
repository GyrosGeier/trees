#include "output_visitor.hpp"

namespace treecc {

void output_visitor::visit(start const &s)
{
    using std::endl;

    action = scan_nonterminals;
    s._1->apply(*this);

    switch(sel)
    {
    case header:
        out << "class const_visitor;" << endl
            << "class visitor;" << endl
            << endl
            << "class invalid_state :" << endl
            << "    public std::logic_error" << endl
            << "{" << endl
            << "public:" << endl
            << "    invalid_state(std::string const &node_type, std::type_info const &visitor_type) :" << endl
            << "        std::logic_error(std::string(visitor_type.name()) + \" does not handle \" + node_type) { }" << endl
            << "};" << endl
            << endl
            << "struct node" << endl
            << "{" << endl
            << "    virtual ~node(void) throw() { }" << endl
            << "    virtual void apply(const_visitor &v) const = 0;" << endl
            << "    virtual void apply(visitor &v) = 0;" << endl
            << "};" << endl;
        out << endl;

        action = emit_fwddecl;
        s._1->apply(*this);

        out << endl;

        action = emit_defn;
        s._1->apply(*this);

        out << endl
            << "class const_visitor" << endl
            << "{" << endl
            << "public:" << endl
            << "    virtual ~const_visitor(void) throw() { }" << endl
            << endl;
        action = emit_constvisitor;
        s._1->apply(*this);
        out << "};" << endl;

        out << endl
            << "class visitor" << endl
            << "{" << endl
            << "public:" << endl
            << "    virtual ~visitor(void) throw() { }" << endl
            << endl;
        action = emit_visitor;
        s._1->apply(*this);
        out << "};" << endl;

        out << endl
            << "class throw_const_visitor :" << endl
            << "    public const_visitor" << endl
            << "{" << endl
            << "public:" << endl
            << "    virtual ~throw_const_visitor(void) throw() { }" << endl
            << endl;
        action = emit_throwconstvisitor;
        s._1->apply(*this);
        out << "};" << endl;

        out << endl
            << "class throw_visitor :" << endl
            << "    public visitor" << endl
            << "{" << endl
            << "public:" << endl
            << "    virtual ~throw_visitor(void) throw() { }" << endl
            << endl;
        action = emit_throwvisitor;
        s._1->apply(*this);
        out << "};" << endl;

        out << endl
            << "class descend_const_visitor :" << endl
            << "    public const_visitor" << endl
            << "{" << endl
            << "public:" << endl
            << "    virtual ~descend_const_visitor(void) throw() { }" << endl
            << endl;
        action = emit_descendconstvisitor;
        s._1->apply(*this);
        out << "};" << endl;

        out << endl
            << "class descend_visitor :" << endl
            << "    public visitor" << endl
            << "{" << endl
            << "public:" << endl
            << "    virtual ~descend_visitor(void) throw() { }" << endl
            << endl;
        action = emit_descendvisitor;
        s._1->apply(*this);
        out << "};" << endl;

        break;

    case source:
        action = emit_dtor;
        s._1->apply(*this);
        action = emit_constapply;
        s._1->apply(*this);
        action = emit_apply;
        s._1->apply(*this);
        action = emit_throwconstvisit;
        s._1->apply(*this);
        action = emit_throwvisit;
        s._1->apply(*this);
        action = emit_descendconstvisit;
        s._1->apply(*this);
        action = emit_descendvisit;
        s._1->apply(*this);

        break;
    }
}

void output_visitor::visit(rules_1 const &)
{
    /* empty */
    return;
}

void output_visitor::visit(rules_2 const &r)
{
    r._1->apply(*this);
    r._2->apply(*this);
}

void output_visitor::visit(rule const &r)
{
    using std::endl;

    switch(action)
    {
    case scan_nonterminals:
        nonterminal_p[r._1] = true;
        break;

    case emit_fwddecl:
        out << "struct " << r._1 << ";" << endl;
        break;

    case emit_defn:
    case emit_constvisitor:
    case emit_visitor:
    case emit_throwconstvisitor:
    case emit_throwvisitor:
    case emit_descendconstvisitor:
    case emit_descendvisitor:
    case emit_dtor:
    case emit_constapply:
    case emit_apply:
    case emit_throwconstvisit:
    case emit_throwvisit:
    case emit_descendconstvisit:
    case emit_descendvisit:
        alternative_count = 0;

        current_rule = &r;
        r._2->apply(*this);
        break;

    default:
        throw;
    }
}

void output_visitor::visit(alternatives_1 const &r)
{
    /* list of components */

    using std::endl;

    switch(action)
    {
    case emit_defn:
        out << "struct " << current_rule->_1;

        switch(alternative_count)
        {
        case 0:
            out << " :" << endl
                << "    public node" << endl;
            break;

        case 1:
            out << " : public node" << endl
                << "{" << endl
                << "    virtual ~" << current_rule->_1 << "(void) throw() { }" << endl
                << "};" << endl
                << endl
                << "struct " << current_rule->_1;
            /* fall through */

        default:
            out << "_" << alternative_count << " :" << endl
                << "    public " << current_rule->_1 << endl;
        }

        out << "{" << endl;

        action = emit_ctor;
        component_count = 0;
        r._1->apply(*this);

        out << "    virtual ~" << current_rule->_1;

        if(alternative_count != 0)
            out << "_" << alternative_count;
        out << "(void) throw();" << endl
            << endl
            << "    virtual void apply(const_visitor &) const;" << endl
            << "    virtual void apply(visitor &);" << endl
            << endl;

        action = emit_members;
        component_count = 0;
        r._1->apply(*this);

        action = emit_defn;

        out << "};" << endl
            << endl;

        break;

    case emit_constvisitor:
    case emit_visitor:
    case emit_throwconstvisitor:
    case emit_throwvisitor:
    case emit_descendconstvisitor:
    case emit_descendvisitor:
        out << "    virtual void visit(" << current_rule->_1;
        if(alternative_count)
            out << "_" << alternative_count;

        switch(action)
        {
        case emit_constvisitor:
        case emit_throwconstvisitor:
        case emit_descendconstvisitor:
            out << " const";
            break;
        case emit_visitor:
        case emit_throwvisitor:
        case emit_descendvisitor:
            break;
        default:
            throw;
        }

        out << " &)";

        switch(action)
        {
        case emit_constvisitor:
        case emit_visitor:
            out << " = 0";
            break;
        case emit_throwconstvisitor:
        case emit_throwvisitor:
        case emit_descendconstvisitor:
        case emit_descendvisitor:
            break;
        default:
            throw;
        }
        
        out << ";" << endl;

        break;

    case emit_dtor:
        out << current_rule->_1;
        if(alternative_count)
            out << "_" << alternative_count;
        out << "::~" << current_rule->_1;
        if(alternative_count)
            out << "_" << alternative_count;
        out << "(void) throw()" << endl
            << "{" << endl;
        component_count = 0;
        r._1->apply(*this);
        out << "}" << endl
            << endl;
        break;

    case emit_constapply:
        out << "void " << current_rule->_1;
        if(alternative_count)
            out << "_" << alternative_count;
        out << "::apply(const_visitor &v) const" << endl
            << "{" << endl
            << "    v.visit(*this);" << endl
            << "}" << endl
            << endl;
        break;

    case emit_apply:
        out << "void " << current_rule->_1;
        if(alternative_count)
            out << "_" << alternative_count;
        out << "::apply(visitor &v)" << endl
            << "{" << endl
            << "    v.visit(*this);" << endl
            << "}" << endl
            << endl;
        break;

    case emit_throwconstvisit:
        out << "void throw_const_visitor::visit(" << current_rule->_1;
        if(alternative_count)
            out << "_" << alternative_count;
        out << " const &)" << endl
            << "{" << endl
            << "    throw invalid_state(\"" << current_rule->_1;
        if(alternative_count)
            out << "_" << alternative_count;
        out << "\", typeid(*this));" << endl
            << "}" << endl
            << endl;
        break;

    case emit_throwvisit:
        out << "void throw_visitor::visit(" << current_rule->_1;
        if(alternative_count)
            out << "_" << alternative_count;
        out << " &)" << endl
            << "{" << endl
            << "    throw invalid_state(\"" << current_rule->_1;
        if(alternative_count)
            out << "_" << alternative_count;
        out << "\", typeid(*this));" << endl
            << "}" << endl
            << endl;
        break;

    case emit_descendconstvisit:
        out << "void descend_const_visitor::visit(" << current_rule->_1;
        if(alternative_count)
            out << "_" << alternative_count;
        out << " const &";
        component_count = 0;
        r._1->apply(*this);
        out << "}" << endl
            << endl;
        break;

    case emit_descendvisit:
        out << "void descend_visitor::visit(" << current_rule->_1;
        if(alternative_count)
            out << "_" << alternative_count;
        out << " &";
        component_count = 0;
        r._1->apply(*this);
        out << "}" << endl
            << endl;
        break;

    default:
        throw;
    }

    ++alternative_count;
}

void output_visitor::visit(alternatives_2 const &r)
{
    /* list of alternatives */
    using std::endl;

    if(alternative_count == 0)
        alternative_count = 1;

    r._1->apply(*this);

    switch(action)
    {
    case emit_defn:
        out << "struct " << current_rule->_1 << "_" << alternative_count << " :" << endl
                << "    public " << current_rule->_1 << endl;

        out << "{" << endl;

        action = emit_ctor;
        component_count = 0;
        r._2->apply(*this);

        out << "    virtual ~" << current_rule->_1 << "_" << alternative_count << "(void) throw();" << endl
            << endl
            << "    virtual void apply(const_visitor &) const;" << endl
            << "    virtual void apply(visitor &);" << endl
            << endl;

        action = emit_members;
        component_count = 0;
        r._2->apply(*this);

        action = emit_defn;

        out << "};" << endl
            << endl;
        break;

    case emit_constvisitor:
    case emit_visitor:
    case emit_throwconstvisitor:
    case emit_throwvisitor:
    case emit_descendconstvisitor:
    case emit_descendvisitor:
        out << "    virtual void visit(" << current_rule->_1 << "_" << alternative_count;
        switch(action)
        {
        case emit_constvisitor:
        case emit_throwconstvisitor:
        case emit_descendconstvisitor:
            out << " const";
            break;
        case emit_visitor:
        case emit_throwvisitor:
        case emit_descendvisitor:
            break;
        default:
            throw;
        }
        out << " &)";

        switch(action)
        {
        case emit_constvisitor:
        case emit_visitor:
            out << " = 0";
            break;
        case emit_throwconstvisitor:
        case emit_throwvisitor:
        case emit_descendconstvisitor:
        case emit_descendvisitor:
            break;
        default:
            throw;
        }
        out << ";" << endl;
        break;

    case emit_dtor:
        out << current_rule->_1 << "_" << alternative_count << "::~"
            << current_rule->_1 << "_" << alternative_count << "(void) throw()" << endl
            << "{" << endl;
        component_count = 0;
        r._2->apply(*this);
        out << "}" << endl
            << endl;
        break;

    case emit_constapply:
        out << "void " << current_rule->_1 << "_" << alternative_count << "::apply(const_visitor &v) const" << endl
            << "{" << endl
            << "    v.visit(*this);" << endl
            << "}" << endl
            << endl;
        break;

    case emit_apply:
        out << "void " << current_rule->_1 << "_" << alternative_count << "::apply(visitor &v)" << endl
            << "{" << endl
            << "    v.visit(*this);" << endl
            << "}" << endl
            << endl;
        break;

    case emit_throwconstvisit:
        out << "void throw_const_visitor::visit(" << current_rule->_1 << "_" << alternative_count << " const &)" << endl
            << "{" << endl
            << "    throw invalid_state(\"" << current_rule->_1 << "_" << alternative_count << "\", typeid(*this));" << endl
            << "}" << endl
            << endl;
        break;

    case emit_throwvisit:
        out << "void throw_visitor::visit(" << current_rule->_1 << "_" << alternative_count << " &)" << endl
            << "{" << endl
            << "    throw invalid_state(\"" << current_rule->_1 << "_" << alternative_count << "\", typeid(*this));" << endl
            << "}" << endl
            << endl;
        break;

    case emit_descendconstvisit:
        out << "void descend_const_visitor::visit(" << current_rule->_1 << "_" << alternative_count << " const &";
        component_count = 0;
        r._2->apply(*this);
        out << "}" << endl
            << endl;
        break;

    case emit_descendvisit:
        out << "void descend_visitor::visit(" << current_rule->_1 << "_" << alternative_count << " &";
        component_count = 0;
        r._2->apply(*this);
        out << "}" << endl
            << endl;
        break;

    default:
        throw;
    }

    ++alternative_count;
}

void output_visitor::visit(alternatives_3 const &r)
{
    /* semicolon terminated rule */
    r._1->apply(*this);
}

void output_visitor::visit(components_1 const &r)
{
    /* empty */

    using std::endl;

    switch(action)
    {
    case emit_descendconstvisit:
    case emit_descendvisit:
        if(component_count == 0)
            out << ")" << endl
                << "{" << endl;
        break;
    default:
        break;
    }
}

void output_visitor::visit(components_2 const &r)
{
    using std::endl;

    bool top = (component_count == 0);

    if(top)
        switch(action)
        {
        case emit_ctor:
            if(alternative_count)
                out << "    " << current_rule->_1 << "_" << alternative_count << "(";
            else
                out << "    " << current_rule->_1 << "(";
            break;
        case emit_descendconstvisit:
        case emit_descendvisit:
            out << "node)" << endl
                << "{" << endl;
            break;
        default:
            break;
        }

    component_count = 1;
    r._1->apply(*this);
    r._2->apply(*this);

    if(top)
        switch(action)
        {
        case emit_ctor:
            out << ")";
            if(component_count > 1)
            {
                out << " : ";
                for(unsigned int i = 1;;)
                {
                    out << "_" << i << "(_" << i << ")";
                    ++i;
                    if(i == component_count)
                        break;
                    out << ", ";
                }
            }
            out << " { }" << endl;
            break;
        case emit_members:
        case emit_dtor:
        case emit_constapply:
        case emit_apply:
        case emit_descendconstvisit:
        case emit_descendvisit:
            break;
        default:
            throw;
        }

}

void output_visitor::visit(component_1 const &r)
{
    /* symbol */
    r._1->apply(*this);
    /* another rule */
}

void output_visitor::visit(component_2 const &r)
{
    /* action */
}

void output_visitor::visit(symbol_1 const &r)
{
    using std::endl;

    switch(action)
    {
    case emit_ctor:
        if(component_count > 1)
            out << ", ";
        if(nonterminal_p[r._1])
            out << r._1 << " *";
        else
            out << "std::string const &";
        out << "_" << component_count;
        break;
    case emit_members:
        if(nonterminal_p[r._1])
            out << "    " << r._1 << " *_";
        else
            out << "    std::string _";
        out << component_count << ";" << endl;
        break;
    case emit_dtor:
        if(nonterminal_p[r._1])
            out << "    delete _" << component_count << ";" << endl;
        break;
    case emit_constapply:
    case emit_apply:
        break;
    case emit_descendconstvisit:
    case emit_descendvisit:
        if(nonterminal_p[r._1])
            out << "    node._" << component_count << "->apply(*this);" << endl;
        break;
    default:
        throw;
    }
    ++component_count;
    /* token reference */
}

void output_visitor::visit(symbol_2 const &r)
{
    /* string */
}

}
