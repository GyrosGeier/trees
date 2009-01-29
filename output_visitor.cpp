#include "output_visitor.hpp"

void output_visitor::visit(start const &s)
{
    using std::endl;

    action = scan_nonterminals;
    s._1->apply(*this);

    switch(sel)
    {
    case header:
        out << "class const_visitor;" << endl
            << endl
            << "struct node" << endl
            << "{" << endl
            << "    virtual ~node(void) throw() { }" << endl
            << "    virtual void apply(const_visitor &v) const = 0;" << endl
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
        break;

    case source:
        action = emit_dtorapply;
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
    case emit_dtorapply:
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
            << endl;

        action = emit_members;
        component_count = 0;
        r._1->apply(*this);

        action = emit_defn;

        out << "};" << endl
            << endl;

        break;

    case emit_constvisitor:
        switch(alternative_count)
        {
        case 0:
            out << "    virtual void visit(" << current_rule->_1 << " const &) = 0;" << endl;
            break;
        default:
            out << "    virtual void visit(" << current_rule->_1 << "_" << alternative_count << " const &) = 0;" << endl;
        }
        break;

    case emit_dtorapply:
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
            << endl
            << "void " << current_rule->_1;
        if(alternative_count)
            out << "_" << alternative_count;
        out << "::apply(const_visitor &v) const" << endl
            << "{" << endl
            << "    v.visit(*this);" << endl
            << "}" << endl
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
            << endl;

        action = emit_members;
        component_count = 0;
        r._2->apply(*this);

        action = emit_defn;

        out << "};" << endl
            << endl;
        break;

    case emit_constvisitor:
        out << "    virtual void visit(" << current_rule->_1 << "_" << alternative_count << " const &) = 0;" << endl;
        break;

    case emit_dtorapply:
        out << current_rule->_1 << "_" << alternative_count << "::~"
            << current_rule->_1 << "_" << alternative_count << "(void) throw()" << endl
            << "{" << endl;
        component_count = 0;
        r._2->apply(*this);
        out << "}" << endl
            << endl
            << "void " << current_rule->_1 << "_" << alternative_count << "::apply(const_visitor &v) const" << endl
            << "{" << endl
            << "    v.visit(*this);" << endl
            << "}" << endl
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
        case emit_dtorapply:
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
    case emit_dtorapply:
        if(nonterminal_p[r._1])
            out << "    delete _" << component_count << ";" << endl;
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
