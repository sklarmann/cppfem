
#include <preprocessDefine.h>

#include <equations/DegreeOfFreedom.h>
#include <control/OutputHandler.h>
#include <iomanip>
#include <pointercollection/pointercollection.h>
#include <control/HandlingStructs.h>


namespace FEMProject {


	template<typename prec, typename uint>
	DegreeOfFreedom<prec,uint>::DegreeOfFreedom() {
		this->status = dofStatus::active;
	}

	template<typename prec, typename uint>
	inline void DegreeOfFreedom<prec, uint>::print(PointerCollection<prec, uint>& pointers)
	{
		OutputHandler &Log = pointers.getInfoData()->Log;
		Log(LogLevel::FullLog, LogLevel::BasicLog) <<
			std::left << std::setw(20) << "Degree of freedom:" <<
			std::right << std::setw(10) << this->id <<
			std::left << std::setw(20) << "  Equation id:" <<
			std::right << std::setw(10) << this->eqid <<
			"  Status:  ";

		if (this->status == dofStatus::active) {
			Log(LogLevel::FullLog, LogLevel::BasicLog) << "active" << std::endl;
		}
		else if (this->status == dofStatus::inactive) {
			Log(LogLevel::FullLog, LogLevel::BasicLog) << "inactive" << std::endl;
		}
		else if (this->status == dofStatus::linked) {
			Log(LogLevel::FullLog, LogLevel::BasicLog) << "linked to Dof " << this->master << std::endl;
		}
	}

}

instantiate(DegreeOfFreedom)