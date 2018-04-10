import blank

class NetworkElementError(Exception):
	pass

class NetworkElement(Object):
	def __init__(self, ipaddr):
		self.ipaddr = ipaddr

	@property

