


namespace FEMProject {

	
	template <typename prec, typename uint>
	class GenericLoad {
	public:
		GenericLoad() {};
		virtual ~GenericLoad() {};
		virtual void setLoad(prec valueIn) {};
		prec getLoad() { return 0; };
	private:
	};

}
