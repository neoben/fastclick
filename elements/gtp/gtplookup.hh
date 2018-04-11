#ifndef CLICK_GTPLookup_HH
#define CLICK_GTPLookup_HH
#include <click/batchelement.hh>
#include <click/ipflowid.hh>
#include <click/hashtablemp.hh>
CLICK_DECLS


/*
=c

GTPLookup()

=s gtp

decapsulate the GTP packet and set the GTP TEID in the aggregate annotation

=d

=a GTPEncap
*/

class GTPTable;

class GTPLookup : public BatchElement { public:

    GTPLookup() CLICK_COLD;
    ~GTPLookup() CLICK_COLD;

    const char *class_name() const	{ return "GTPLookup"; }
    const char *port_count() const	{ return "1/1"; }
    const char *flow_code() const  { return "x/x"; }
    const char *flags() const		{ return PUSH; }

    int configure(Vector<String> &, ErrorHandler *) CLICK_COLD;
    bool can_live_reconfigure() const	{ return true; }

    bool run_task(Task*) override;

    int process(int, Packet*);
    void push(int, Packet *) override;
#if HAVE_BATCH
	void push_batch(int port, PacketBatch *) override;
#endif
  private:
	GTPTable *_table;
    atomic_uint32_t _id;
    per_thread<Packet*> _queue;


};

CLICK_ENDDECLS
#endif
