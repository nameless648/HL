#include "KDTags.h"

namespace KDTags
{
	namespace KDAbilities
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary , "KDTags.KDAbilities.Primary" , "Tag for the Ability");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Secondary , "KDTags.KDAbilities.Secondary" , "Tag for the Ability");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tertiary , "KDTags.KDAbilities.Tertiary" , "Tag for the Ability");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActivateOnGiven , "KDTags.KDAbilities.ActivateOnGiven" , "Tag for Abilities that should activate immediately once given");
	}
	namespace Event
	{
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact , "KDTags.Event.Enemy.HitReact" , "Tag for the Enemy HitReact Event");
		}
	}
}