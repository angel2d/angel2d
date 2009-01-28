#include "Biped.h"
#include "BipedDef.h"

Biped::Biped(b2World* w, const b2Vec2& position)				
{
	m_world = w;

	BipedDef def;
	b2BodyDef bd;

	// create body parts
	bd = def.LFootDef;
	bd.position += position;
	LFoot = w->CreateBody(&bd);
	LFoot->CreateShape(&def.LFootPoly);
	LFoot->SetMassFromShapes();

	bd = def.RFootDef;
	bd.position += position;
	RFoot = w->CreateBody(&bd);
	RFoot->CreateShape(&def.RFootPoly);
	RFoot->SetMassFromShapes();

	bd = def.LCalfDef;
	bd.position += position;
	LCalf = w->CreateBody(&bd);
	LCalf->CreateShape(&def.LCalfPoly);
	LCalf->SetMassFromShapes();

	bd = def.RCalfDef;
	bd.position += position;
	RCalf = w->CreateBody(&bd);
	RCalf->CreateShape(&def.RCalfPoly);
	RCalf->SetMassFromShapes();

	bd = def.LThighDef;
	bd.position += position;
	LThigh = w->CreateBody(&bd);
	LThigh->CreateShape(&def.LThighPoly);
	LThigh->SetMassFromShapes();

	bd = def.RThighDef;
	bd.position += position;
	RThigh = w->CreateBody(&bd);
	RThigh->CreateShape(&def.RThighPoly);
	RThigh->SetMassFromShapes();

	bd = def.PelvisDef;
	bd.position += position;
	Pelvis = w->CreateBody(&bd);
	Pelvis->CreateShape(&def.PelvisPoly);
	Pelvis->SetMassFromShapes();

	bd = def.PelvisDef;
	bd.position += position;
	Stomach = w->CreateBody(&bd);
	Stomach->CreateShape(&def.StomachPoly);
	Stomach->SetMassFromShapes();

	bd = def.ChestDef;
	bd.position += position;
	Chest = w->CreateBody(&bd);
	Chest->CreateShape(&def.ChestPoly);
	Chest->SetMassFromShapes();

	bd = def.NeckDef;
	bd.position += position;
	Neck = w->CreateBody(&bd);
	Neck->CreateShape(&def.NeckPoly);
	Neck->SetMassFromShapes();

	bd = def.HeadDef;
	bd.position += position;
	Head = w->CreateBody(&bd);
	Head->CreateShape(&def.HeadCirc);
	Head->SetMassFromShapes();

	bd = def.LUpperArmDef;
	bd.position += position;
	LUpperArm = w->CreateBody(&bd);
	LUpperArm->CreateShape(&def.LUpperArmPoly);
	LUpperArm->SetMassFromShapes();

	bd = def.RUpperArmDef;
	bd.position += position;
	RUpperArm = w->CreateBody(&bd);
	RUpperArm->CreateShape(&def.RUpperArmPoly);
	RUpperArm->SetMassFromShapes();

	bd = def.LForearmDef;
	bd.position += position;
	LForearm = w->CreateBody(&bd);
	LForearm->CreateShape(&def.LForearmPoly);
	LForearm->SetMassFromShapes();

	bd = def.RForearmDef;
	bd.position += position;
	RForearm = w->CreateBody(&bd);
	RForearm->CreateShape(&def.RForearmPoly);
	RForearm->SetMassFromShapes();

	bd = def.LHandDef;
	bd.position += position;
	LHand = w->CreateBody(&bd);
	LHand->CreateShape(&def.LHandPoly);
	LHand->SetMassFromShapes();

	bd = def.RHandDef;
	bd.position += position;
	RHand = w->CreateBody(&bd);
	RHand->CreateShape(&def.RHandPoly);
	RHand->SetMassFromShapes();
	
	// link body parts
	def.LAnkleDef.body1		= LFoot;
	def.LAnkleDef.body2		= LCalf;
	def.RAnkleDef.body1		= RFoot;
	def.RAnkleDef.body2		= RCalf;
	def.LKneeDef.body1		= LCalf;
	def.LKneeDef.body2		= LThigh;
	def.RKneeDef.body1		= RCalf;
	def.RKneeDef.body2		= RThigh;
	def.LHipDef.body1		= LThigh;
	def.LHipDef.body2		= Pelvis;
	def.RHipDef.body1		= RThigh;
	def.RHipDef.body2		= Pelvis;
	def.LowerAbsDef.body1	= Pelvis;
	def.LowerAbsDef.body2	= Stomach;
	def.UpperAbsDef.body1	= Stomach;
	def.UpperAbsDef.body2	= Chest;
	def.LowerNeckDef.body1	= Chest;
	def.LowerNeckDef.body2	= Neck;
	def.UpperNeckDef.body1	= Chest;
	def.UpperNeckDef.body2	= Head;
	def.LShoulderDef.body1	= Chest;
	def.LShoulderDef.body2	= LUpperArm;
	def.RShoulderDef.body1	= Chest;
	def.RShoulderDef.body2	= RUpperArm;
	def.LElbowDef.body1		= LForearm;
	def.LElbowDef.body2		= LUpperArm;
	def.RElbowDef.body1		= RForearm;
	def.RElbowDef.body2		= RUpperArm;
	def.LWristDef.body1		= LHand;
	def.LWristDef.body2		= LForearm;
	def.RWristDef.body1		= RHand;
	def.RWristDef.body2		= RForearm;
	
	// create joints
	LAnkle		= (b2RevoluteJoint*)w->CreateJoint(&def.LAnkleDef);
	RAnkle		= (b2RevoluteJoint*)w->CreateJoint(&def.RAnkleDef);
	LKnee		= (b2RevoluteJoint*)w->CreateJoint(&def.LKneeDef);
	RKnee		= (b2RevoluteJoint*)w->CreateJoint(&def.RKneeDef);
	LHip		= (b2RevoluteJoint*)w->CreateJoint(&def.LHipDef);
	RHip		= (b2RevoluteJoint*)w->CreateJoint(&def.RHipDef);
	LowerAbs	= (b2RevoluteJoint*)w->CreateJoint(&def.LowerAbsDef);
	UpperAbs	= (b2RevoluteJoint*)w->CreateJoint(&def.UpperAbsDef);
	LowerNeck	= (b2RevoluteJoint*)w->CreateJoint(&def.LowerNeckDef);
	UpperNeck	= (b2RevoluteJoint*)w->CreateJoint(&def.UpperNeckDef);
	LShoulder	= (b2RevoluteJoint*)w->CreateJoint(&def.LShoulderDef);
	RShoulder	= (b2RevoluteJoint*)w->CreateJoint(&def.RShoulderDef);
	LElbow		= (b2RevoluteJoint*)w->CreateJoint(&def.LElbowDef);
	RElbow		= (b2RevoluteJoint*)w->CreateJoint(&def.RElbowDef);
	LWrist		= (b2RevoluteJoint*)w->CreateJoint(&def.LWristDef);
	RWrist		= (b2RevoluteJoint*)w->CreateJoint(&def.RWristDef);
}


Biped::~Biped(void)
{
	m_world->DestroyBody(LFoot);
	m_world->DestroyBody(RFoot);
	m_world->DestroyBody(LCalf);
	m_world->DestroyBody(RCalf);
	m_world->DestroyBody(LThigh);
	m_world->DestroyBody(RThigh);
	m_world->DestroyBody(Pelvis);
	m_world->DestroyBody(Stomach);
	m_world->DestroyBody(Chest);
	m_world->DestroyBody(Neck);
	m_world->DestroyBody(Head);
	m_world->DestroyBody(LUpperArm);
	m_world->DestroyBody(RUpperArm);
	m_world->DestroyBody(LForearm);
	m_world->DestroyBody(RForearm);
	m_world->DestroyBody(LHand);
	m_world->DestroyBody(RHand);
}
