/*------------------------------------------------------------------------------*
 *                       (c)2016, All Rights Reserved.     						*
 *       ___           ___           ___     									*
 *      /__/\         /  /\         /  /\    									*
 *      \  \:\       /  /:/        /  /::\   									*
 *       \  \:\     /  /:/        /  /:/\:\  									*
 *   ___  \  \:\   /  /:/  ___   /  /:/~/:/        								*
 *  /__/\  \__\:\ /__/:/  /  /\ /__/:/ /:/___     UCR DMFB Synthesis Framework  *
 *  \  \:\ /  /:/ \  \:\ /  /:/ \  \:\/:::::/     www.microfluidics.cs.ucr.edu	*
 *   \  \:\  /:/   \  \:\  /:/   \  \::/~~~~ 									*
 *    \  \:\/:/     \  \:\/:/     \  \:\     									*
 *     \  \::/       \  \::/       \  \:\    									*
 *      \__\/         \__\/         \__\/    									*
 *-----------------------------------------------------------------------------*/
/*--------------------------------Class Details---------------------------------*
 * Name: Synthesis																*
 *																				*
 * Details: Contains the primary public functions to be called by end-user.		*
 * EntireFlow(), Schedule(), Place() and Route() are all high level calls.		*
 * Calls all the functions that handle the file I/O for synthesis.				*
 *-----------------------------------------------------------------------------*/
#ifndef _SYNTHESIS_H
#define _SYNTHESIS_H

#include "elapsed_timer.h"
#include "compatibility_check.h"
#include "dmfb_arch.h"
#include "enums.h"
#include "dag.h"
#include "scheduler.h"
#include "placer.h"
#include "router.h"

class Synthesis
{
	private:
		// Methods
		void deleteAndRenewVariables();
		void synthesizeDesign();
		static Scheduler * getNewSchedulingMethod(SchedulerType st);
		static Placer * getNewPlacementMethod(PlacerType pt);
		static Router * getNewRoutingMethod(RouterType rt, DmfbArch *arch);
		static void setPinMappingMethod(PinMapType pmt, ResourceAllocationType rat, DmfbArch *arch);
		static void setWireRoutingMethod(WireRouteType wrt, DmfbArch *arch);
		static void printRoutingStats(vector<unsigned long long> *tsBeginningCycle, DmfbArch *arch);
		static void printWireRoutingStats(DmfbArch *arch);

	protected:
		// Variables
		Scheduler *scheduler;
		Placer *placer;
		Router *router;
		WireRouter *wireRouter;
		map<Droplet *, vector<RoutePoint *> *> *routes;
		vector<vector<RoutePoint*> *> *dirtyCells;
		vector<vector<int> *> *pinActivations;
		vector<ReconfigModule *> *rModules;
		vector<unsigned long long> *tsBeginningCycle;
		DmfbArch *arch;
		DAG *dag;
		ExecutionType executionType;

	public:
		// Constructors
		Synthesis(SchedulerType st, PlacerType pt, RouterType rt, bool performWash, ResourceAllocationType rat, PinMapType pmt, WireRouteType wrt, CompactionType ct, ProcessEngineType pet, ExecutionType et, DAG *assay, DmfbArch *dmfbArch);
		virtual ~Synthesis();

		static Synthesis *CreateNewSynthesisEngine(string archFile, SchedulerType st, PlacerType pt, RouterType rt, bool performWash, ResourceAllocationType rat, PinMapType pmt, WireRouteType wrt, CompactionType ct, ProcessEngineType pet, ExecutionType et, int maxStorageDropsPerMod, int cellsBetweenModIR, int numHorizTracks, int numVertTracks);

		// Getters/Setters
		Scheduler *getScheduler() { return scheduler; }
		Placer *getPlacer() { return placer; }
		Router *getRouter() { return router; }
		WireRouter *getWireRouter() { return wireRouter; }
		DmfbArch *getArch() { return arch; }

		friend class FileOut;
		friend class FileIn;
};
#endif /* _SYNTHESIS_H */
