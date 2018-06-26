#include "renderpointlocalestimate.h"


RenderPointLocalEstimate::RenderPointLocalEstimate( RenderPoint &_renderPoint )
    : renderPoint( _renderPoint ), counterRaysCos1Zero( 0 ), illuminance( 0 )
{

}
