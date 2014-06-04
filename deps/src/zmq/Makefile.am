noinst_LTLIBRARIES = libzmq.la

opentxs_include_dir	= $(top_srcdir)/include
opentxs_source_dir	= $(top_srcdir)/src

## COMMON FLAGS ###

common_includes = $(AM_CXXFLAGS)

#### Lib OT build calls

libzmq_la_SOURCES = $(libzmq_sources) $(libzmq_headers)

libzmq_la_CXXFLAGS = -I$(libzmq_headers_dir) $(common_includes) 


libzmq_la_LDFLAGS = --no-undefined -static


####################################################################

libzmq_sources	= \
		address.hpp \
		array.hpp \
		atomic_counter.hpp \
		atomic_ptr.hpp \
		blob.hpp \
		clock.hpp \
		command.hpp \
		config.hpp \
		ctx.hpp \
		curve_client.hpp \
		curve_server.hpp \
		decoder.hpp \
		devpoll.hpp \
		dist.hpp \
		encoder.hpp \
		epoll.hpp \
		err.hpp \
		fd.hpp \
		fq.hpp \
		i_encoder.hpp \
		i_decoder.hpp \
		i_engine.hpp \
		i_poll_events.hpp \
		io_object.hpp \
		io_thread.hpp \
		ip.hpp \
		ipc_address.hpp \
		ipc_connecter.hpp \
		ipc_listener.hpp \
		i_engine.hpp \
		i_poll_events.hpp \
		kqueue.hpp \
		lb.hpp \
		likely.hpp \
		mailbox.hpp \
		mechanism.hpp \
		msg.hpp \
		mtrie.hpp \
		mutex.hpp \
		norm_engine.hpp \
		null_mechanism.hpp \
		object.hpp \
		options.hpp \
		own.hpp \
		pgm_receiver.hpp \
		pgm_sender.hpp \
		pgm_socket.hpp \
		pipe.hpp \
		plain_mechanism.hpp \
		platform.hpp \
		poll.hpp \
		poller.hpp \
		poller_base.hpp \
		pair.hpp \
		proxy.hpp \
		pub.hpp \
		pull.hpp \
		push.hpp \
		random.hpp \
		reaper.hpp \
		rep.hpp \
		req.hpp \
		select.hpp \
		session_base.hpp \
		signaler.hpp \
		socket_base.hpp \
		stdint.hpp \
		stream.hpp \
		stream_engine.hpp \
		sub.hpp \
		tcp.hpp \
		tcp_address.hpp \
		tcp_connecter.hpp \
		tcp_listener.hpp \
		thread.hpp \
		trie.hpp \
		windows.hpp \
		wire.hpp \
		xpub.hpp \
		router.hpp \
		dealer.hpp \
		xsub.hpp \
		ypipe.hpp \
		ypipe_base.hpp \
		yqueue.hpp \
		address.cpp \
		clock.cpp \
		ctx.cpp \
		curve_client.cpp \
		curve_server.cpp \
		devpoll.cpp \
		dist.cpp \
		epoll.cpp \
		err.cpp \
		fq.cpp \
		io_object.cpp \
		io_thread.cpp \
		ip.cpp \
		ipc_address.cpp \
		ipc_connecter.cpp \
		ipc_listener.cpp \
		kqueue.cpp \
		lb.cpp \
		mailbox.cpp \
		mechanism.cpp \
		msg.cpp \
		mtrie.cpp \
		norm_engine.cpp \
		null_mechanism.cpp \
		object.cpp \
		options.cpp \
		own.cpp \
		pair.cpp \
		pgm_receiver.cpp \
		pgm_sender.cpp \
		pgm_socket.cpp \
		pipe.cpp \
		plain_mechanism.cpp \
		poll.cpp \
		poller_base.cpp \
		pull.cpp \
		push.cpp \
		proxy.cpp \
		reaper.cpp \
		pub.cpp \
		random.cpp \
		rep.cpp \
		req.cpp \
		select.cpp \
		session_base.cpp \
		signaler.cpp \
		socket_base.cpp \
		stream.cpp \
		stream_engine.cpp \
		sub.cpp \
		tcp.cpp \
		tcp_address.cpp \
		tcp_connecter.cpp \
		tcp_listener.cpp \
		thread.cpp \
		trie.cpp \
		xpub.cpp \
		router.cpp \
		dealer.cpp \
		v1_decoder.cpp \
		v1_encoder.cpp \
		v1_decoder.hpp \
		v1_encoder.hpp \
		v2_decoder.cpp \
		v2_decoder.hpp \
		v2_encoder.cpp \
		v2_encoder.hpp \
		v2_protocol.hpp \
		xsub.cpp \
		zmq.cpp \
		zmq_utils.cpp \
		raw_decoder.hpp \
		raw_decoder.cpp \
		raw_encoder.hpp \
		raw_encoder.cpp \
		ypipe_conflate.hpp \
		dbuffer.hpp \
		tipc_address.cpp \
		tipc_address.hpp \
		tipc_listener.cpp \
		tipc_listener.hpp \
		tipc_connecter.cpp \
		tipc_connecter.hpp



libzmq_headers_dir = $(top_srcdir)/deps/include/zmq

libzmq_headers = \
		$(libzmq_headers_dir)/zmq.h \
		$(libzmq_headers_dir)/zmq_utils.h \
		$(libzmq_headers_dir)/zmq.hpp

