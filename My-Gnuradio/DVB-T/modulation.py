#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Top Block
# Generated: Sat Aug 11 10:34:03 2012
##################################################

from PyQt4 import Qt
from gnuradio import digital
##################################################
#------------------------------------------------#
from gnuradio import dvbt
#from gnuradio import dvbt_swig
#------------------------------------------------#
##################################################
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.gr import firdes
from gnuradio.qtgui import qtgui
from grc_gnuradio import blks2 as grc_blks2
from optparse import OptionParser
import sip
import sys

class top_block(gr.top_block, Qt.QWidget):

	def __init__(self):
		gr.top_block.__init__(self, "Top Block")
		Qt.QWidget.__init__(self)
		self.setWindowTitle("Top Block")
		self.setWindowIcon(Qt.QIcon.fromTheme('gnuradio-grc'))
		self.top_scroll_layout = Qt.QVBoxLayout()
		self.setLayout(self.top_scroll_layout)
		self.top_scroll = Qt.QScrollArea()
		self.top_scroll.setFrameStyle(Qt.QFrame.NoFrame)
		self.top_scroll_layout.addWidget(self.top_scroll)
		self.top_scroll.setWidgetResizable(True)
		self.top_widget = Qt.QWidget()
		self.top_scroll.setWidget(self.top_widget)
		self.top_layout = Qt.QVBoxLayout(self.top_widget)
		self.top_grid_layout = Qt.QGridLayout()
		self.top_layout.addLayout(self.top_grid_layout)


		##################################################
		# Parameters
		##################################################


		##################################################
		# Variables
		##################################################
		self.Modulation_Type = "qam16"
		self.samp_rate = samp_rate = 32000
		self.FFT_LENGTH = FFT_LENGTH = 2048
		self.OCCUPIED_CARRIERS = OCCUPIED_CARRIERS = 1705

		################################################################################################################
                #--------------------------------------------------------------------------------------------------------------#
                #self.input = '/home/katsikas/katsikas-repo/My-Gnuradio/Common/Korgialas_GeiaSou.ts'
                #self.output = '/home/katsikas/Desktop/Results.ts'
                self.input = '/home/katsikas/katsikas-repo/My-Gnuradio/Common/Text.txt'
                self.output = '/home/katsikas/Desktop/sink.txt'
                #--------------------------------------------------------------------------------------------------------------#

                #--------------------------------------------------------------------------------------------------------------#
                #self.gr_file_source_0 = gr.file_source(gr.sizeof_char*1, self.input, False)
                with open(self.input, 'rb'):
                        self.gr_file_source_0 = dvbt.dvbt_source(self.input)

                #self.gr_file_sink_0 = gr.file_sink(gr.sizeof_char*1, self.output)
                #self.gr_file_sink_0.set_unbuffered(False)
                with open(self.output, 'rb'):
                        self.gr_file_sink_0 = dvbt.dvbt_sink(self.output)

                self.stream = gr.vector_to_stream(gr.sizeof_char, 256)
                self.vector = gr.stream_to_vector(gr.sizeof_char, 256)
                #--------------------------------------------------------------------------------------------------------------#
                ################################################################################################################


		##################################################
		# Blocks
		##################################################
		self.qtgui_ofdm_vector_analyzer_x_0 = qtgui.ofdm_vector_analyzer_c(
			  self.OCCUPIED_CARRIERS, #occupied_tones
			  self.Modulation_Type #modulation
			  )
		self._qtgui_ofdm_vector_analyzer_x_0_win = sip.wrapinstance(self.qtgui_ofdm_vector_analyzer_x_0.pyqwidget(), Qt.QWidget)
		self.top_grid_layout.addWidget(self._qtgui_ofdm_vector_analyzer_x_0_win, 
		   )
		self.gr_vector_to_stream_0 = gr.vector_to_stream(gr.sizeof_gr_complex*1, self.OCCUPIED_CARRIERS)
		self.digital_ofdm_mod_0 = grc_blks2.packet_mod_b(digital.dvbt_ofdm_mod(
				options=grc_blks2.options(
					modulation=self.Modulation_Type,
					fft_length=self.FFT_LENGTH,
					occupied_tones=self.OCCUPIED_CARRIERS,
					cp_length=128,
					pad_for_usrp=True,
					log=None,
					verbose=None,
				),
			),
			payload_length=0,
		)
		self.digital_ofdm_demod_0 = grc_blks2.packet_demod_b(digital.dvbt_ofdm_demod(
				options=grc_blks2.options(
					modulation=self.Modulation_Type,
					fft_length=self.FFT_LENGTH,
					occupied_tones=self.OCCUPIED_CARRIERS,
					cp_length=128,
					snr=10,
					show_vector_analyzer="yes",
					log=None,
					verbose=None,
				),
				callback=lambda ok, payload: self.digital_ofdm_demod_0.recv_pkt(ok, payload),
			),
		)
		

		##################################################
		# Connections
		##################################################
                self.connect((self.gr_file_source_0, 0), (self.stream, 0))
                self.connect((self.stream, 0), (self.digital_ofdm_mod_0, 0))
                self.connect((self.digital_ofdm_mod_0, 0), (self.digital_ofdm_demod_0, 0))
		self.connect((self.digital_ofdm_demod_0, 1), (self.gr_vector_to_stream_0, 0))
                self.connect((self.gr_vector_to_stream_0, 0), (self.qtgui_ofdm_vector_analyzer_x_0, 0))
		self.connect((self.digital_ofdm_demod_0, 0), (self.vector, 0))
                self.connect((self.vector, 0), (self.gr_file_sink_0, 0))


		"""
		self.connect((self.digital_ofdm_mod_0, 0), (self.digital_ofdm_demod_0, 0))
		self.connect((self.gr_file_source_0, 0), (self.digital_ofdm_mod_0, 0))
		self.connect((self.digital_ofdm_demod_0, 1), (self.gr_vector_to_stream_0, 0))
		self.connect((self.gr_vector_to_stream_0, 0), (self.qtgui_ofdm_vector_analyzer_x_0, 0))
		self.connect((self.digital_ofdm_demod_0, 0), (self.gr_file_sink_0, 0))
		"""
	def get_samp_rate(self):
		return self.samp_rate

	def set_samp_rate(self, samp_rate):
		self.samp_rate = samp_rate

	def get_OCCUPIED_CARRIERS(self):
		return self.OCCUPIED_CARRIERS

	def set_OCCUPIED_CARRIERS(self, OCCUPIED_CARRIERS):
		self.OCCUPIED_CARRIERS = OCCUPIED_CARRIERS

	def get_FFT_LENGTH(self):
		return self.FFT_LENGTH

	def set_FFT_LENGTH(self, FFT_LENGTH):
		self.FFT_LENGTH = FFT_LENGTH


if __name__ == '__main__':
	parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
	(options, args) = parser.parse_args()
	qapp = Qt.QApplication(sys.argv)
	tb = top_block()
	tb.start()
	tb.show()
	qapp.exec_()
	tb.stop()

