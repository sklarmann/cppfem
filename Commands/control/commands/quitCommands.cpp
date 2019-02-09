


#include <control/commands/GenericCommand.h>
#include <control/stringCommandHandler.h>
#include <control/OutputHandler.h>

namespace FEMProject {
	namespace Commands {

		/**
		* @class Command to end the program.
		*/
		template<typename prec, typename uint>
		class macroQuit : public GenericCommand<prec, uint> {
		public:
			macroQuit(stringCommandHandler &cmd) {};
			~macroQuit() {};
			void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
		private:


		};


		template<typename prec, typename uint>
		void macroQuit<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
			program->disableUserMacro();
		}

		/**
		* @brief Command to quit mesh processor.
		*/
		template<typename prec, typename uint>
		class meshQuit : public GenericCommand<prec, uint> {
		public:
			meshQuit(stringCommandHandler &cmd) {};
			~meshQuit() {};
			void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
		private:


		};


		template<typename prec, typename uint>
		void meshQuit<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
			program->disableUserMesh();
		}

		/**
		* @brief Command to start mesh processor.
		*/
		template<typename prec, typename uint>
		class meshInteract : public GenericCommand<prec, uint> {
		public:
			meshInteract(stringCommandHandler &cmd) {};
			~meshInteract() {};
			void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
		private:


		};


		template<typename prec, typename uint>
		void meshInteract<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
			program->enableUserMesh();
		}

		/**
		* @brief Command to quit plot processor.
		*/
		template<typename prec, typename uint>
		class plotQuit : public GenericCommand<prec, uint> {
		public:
			plotQuit(stringCommandHandler &cmd) {};
			~plotQuit() {};
			void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
		private:


		};


		template<typename prec, typename uint>
		void plotQuit<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
			program->disableUserPlot();
		}

		/**
		* @brief Command to start plot processor.
		*/
		template<typename prec, typename uint>
		class plotInteract : public GenericCommand<prec, uint> {
		public:
			plotInteract(stringCommandHandler &cmd) {};
			~plotInteract() {};
			void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
		private:


		};


		template<typename prec, typename uint>
		void plotInteract<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
			program->enableUserPlot();
		}

		/**
		* @brief Command to quit math processor.
		*/
		template<typename prec, typename uint>
		class mathQuit : public GenericCommand<prec, uint> {
		public:
			mathQuit(stringCommandHandler &cmd) {};
			~mathQuit() {};
			void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
		private:


		};


		template<typename prec, typename uint>
		void mathQuit<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
			program->disableUserMath();
		}

		/**
		* @brief Command to start math processor.
		*/
		template<typename prec, typename uint>
		class mathInteract : public GenericCommand<prec, uint> {
		public:
			mathInteract(stringCommandHandler &cmd) {};
			~mathInteract() {};
			void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
		private:


		};


		template<typename prec, typename uint>
		void mathInteract<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
			program->enableUserMath();
		}
	}
}
